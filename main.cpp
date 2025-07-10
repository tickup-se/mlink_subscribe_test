// protobuf_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "spiderrock_mlink.hpp"
#include "spiderrock_protobuf.hpp"
#include "ticker_list.h"

uint64_t gOpenCrossTrades = 0;
uint64_t gCloseCrossTrades = 0;

std::map<std::string, uint64_t> gUniqueOpenCross;
std::map<std::string, uint64_t> gUniqueCloseCross;

static std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);
    std::stringstream ss;
    ss << std::put_time(local_time, "%H:%M:%S") << " [" << local_time->tm_zone << "]";
    return ss.str();
}

void onCrossTrade(const std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo> &rCrossTrade) {
    if (rCrossTrade->mAucionType == spiderrock::protobuf::api::Observer::AuctionType::open) {
        gOpenCrossTrades++;
        gUniqueOpenCross[rCrossTrade->mTicker] += 1;
    } else if (rCrossTrade->mAucionType == spiderrock::protobuf::api::Observer::AuctionType::close) {
        gCloseCrossTrades++;
        gUniqueCloseCross[rCrossTrade->mTicker] += 1;
    } else {
        std::cout << "Unknown auction type" << std::endl;
    }
}

int main(int argc, char *argv[]) {

    //Get the program arguments

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <SpiderRock key>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string lSpiderRockKey = argv[1];
    if (lSpiderRockKey.length() < 5) {
        std::cerr << "Error: SpiderRock key is not set or too short." << std::endl;
        return EXIT_FAILURE;
    }
    std::string lMaskedKey = std::string(7, '*') + lSpiderRockKey.substr(lSpiderRockKey.length() - 3, 3);
    std::cout << "SpiderRock key: " << lMaskedKey << std::endl;

    //Populate the ticker list

    std::vector<std::string> lTickerList = getTickerVector();
    if (lTickerList.empty()) {
        std::cerr << "Error: No tickers found." << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Got: " << lTickerList.size() << " tickers." << std::endl;

    //Start of Spiderrocks example code from their Github-repo
    //Got no clue about the first 'rest session' part. it's original fails added port 443 then at least the code continues

    std::vector<char> lBuffer(65536 + 1, 0);
    spiderrock::mlink::Context context;

    //Start of the web socket part (Connect)
    spiderrock::mlink::MLinkSession ws_session(context);

    bool result = ws_session.connect("wss://mlink-live.nms.saturn.spiderrockconnect.com/mlink/proto", lSpiderRockKey);

    if (!result) {
        result = ws_session.connect("ws://mlink.saturn.srplatform.net:6700/mlink/proto", lSpiderRockKey);
        if (!result) {
            std::cout << ws_session.getLastError() << std::endl;
            exit(-1);
        }
    }

    //generate the handlers
    spiderrock::mlink::SubscriptionManager<> mgr(ws_session);
    spiderrock::protobuf::api::Observer lObserver;

    //This callback traverses the incoming data
    //the data is feed the observer got callbacks for stockprint ending up in the method 'onCrossTrade' above

    mgr.start([&lObserver](char *buffer, size_t bytesRead) {
            if (buffer[0] == '\r' && buffer[1] == '\n') {
                if (buffer[2] == 'P') {
                    lObserver.process_buffer(buffer, static_cast<int>(bytesRead));
                } else {
                    buffer[bytesRead] = 0;
                    std::cout << buffer << std::endl;
                }
            } else {
                buffer[bytesRead] = 0;
                std::cout << buffer << std::endl;
            }
        }
    );

    uint64_t lStreamState = 0;
    std::atomic<bool> lStreamCompleted= false;

    //The below handler is making sure a stream request passes, begin, active, complete before initiating a new stream request.

    lObserver.mMLinkStreamCheckPtCallback = [&lStreamState, &lStreamCompleted](std::unique_ptr<spiderrock::protobuf::api::Observer::StreamData> pStrmData) {
        if (pStrmData->mResult == spiderrock::protobuf::api::MLinkStreamState::MLINKSTREAMSTATE_BEGIN) {
            if (lStreamState != 0) {
                throw std::runtime_error("Stream start failed");
            }
            lStreamState = 1;
        } else if (pStrmData->mResult == spiderrock::protobuf::api::MLinkStreamState::MLINKSTREAMSTATE_ACTIVE) {
            if (lStreamState != 1) {
                throw std::runtime_error("Stream active failed");
            }
            lStreamState = 2;

        }else if (pStrmData->mResult == spiderrock::protobuf::api::MLinkStreamState::MLINKSTREAMSTATE_COMPLETE) {
            if (lStreamState != 2) {
                throw std::runtime_error("Stream complete failed");
            }
            lStreamState = 0;
            lStreamCompleted = true;
        } else {
            std::cout << "Unknown stream state" << std::endl;
            lStreamState = 0;
            lStreamCompleted = false;
        }
    };

    //get all open and close crosses in the above function: onCrossTrade
    lObserver.mCrossTradeCallback = onCrossTrade;

    //Set up the stream basics
    int activeLatency = 1;
    std::string messageType = "StockPrint";
    std::string queryString = messageType + "_Query";

    spiderrock::protobuf::api::MLinkStream mlinkStream;
    mlinkStream.set_active_latency(activeLatency);
    mlinkStream.set_msg_name(messageType);
    mlinkStream.set_query_label(queryString);

    //This loop is extracting batches of 50 tickers and builds the spiderrock formated ticker filter string.
    //Then it starts the stream with the filter string and waits for the stream to be reported successfull from the backend
    std::string lSubscribeToInstruments;
    uint64_t lBreakCount = 0;
    uint64_t lSubStreamCounter = 0;
    for (const auto &rTickerName: lTickerList) {
        lSubscribeToInstruments += "ticker.tk:eq:" + rTickerName;
        lSubStreamCounter++;
        lBreakCount++;
        //Stream batches of 50 tickers at a time.
        if (lBreakCount > 50) {
            mlinkStream.set_where_clause(lSubscribeToInstruments);
            mgr.stream(mlinkStream);
            lSubscribeToInstruments = "";
            lBreakCount = 0;

            //wait for the backend to accept the stream
            uint64_t lTimeout = 5000; //5 seconds timeout
            while (!lStreamCompleted) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                if (!lTimeout--) {
                    std::cout << "subscribe string: " << lSubscribeToInstruments << std::endl;
                    throw std::runtime_error("timeout waiting for stream response");
                }
            }
            lStreamCompleted = false;
        } else {
            lSubscribeToInstruments += " | ";
        }
    }

    //If we got less than 50 instruments last loop ask to stream the tail.
    if (!lSubscribeToInstruments.empty()) {
        //Remove the last three characters from the string lSubscribeToInstruments to remove the last " | "
        lSubscribeToInstruments.erase(lSubscribeToInstruments.size() - 3, 3);
        mlinkStream.set_where_clause(lSubscribeToInstruments);
        mgr.stream(mlinkStream);

        //wait for the backend to accept the stream
        uint64_t lTimeout = 5000; //5 seconds timeout
        while (!lStreamCompleted) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (!lTimeout--) {
                std::cout << "Subscribe string: " << lSubscribeToInstruments << std::endl;
                throw std::runtime_error("Timeout waiting for stream response");
            }
        }
        lStreamCompleted = false;
    }
    std::cout << "MLink stream: " << lSubStreamCounter << " instruments in total" << std::endl;

    //detach a thread printing the global debug counters
    std::thread ([&lObserver]() {
        while (true) {
            //sleep for 10 seconds
            std::this_thread::sleep_for(std::chrono::seconds(10));
            std::cout << "(time: " << getCurrentTime()
                << ") open cross trades: " << gOpenCrossTrades
                << " close cross trades: " << gCloseCrossTrades
                << " unique open: " << gUniqueOpenCross.size()
                << " unique close: " << gUniqueCloseCross.size()
                << " no. print messages: " << lObserver.mNumberPrintMessages
                << std::endl;
        }
    }).detach();

    //We will never end.. Skip garbage collection.
    mgr.join();
    //mgr.shutDown();
    //ws_session.cleanup();

    return EXIT_SUCCESS;
}
