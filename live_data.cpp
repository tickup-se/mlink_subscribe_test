// protobuf_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>
#include "ticker_list.h"
#include "MLinkStreamHandler.h"

uint64_t gOpenCrossTrades = 0;
uint64_t gCloseCrossTrades = 0;

std::map<std::string, uint64_t> gUniqueOpenCross;
std::map<std::string, uint64_t> gUniqueCloseCross;

std::mutex gCrossTradeMtx;

static std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);
    std::stringstream ss;
    ss << std::put_time(local_time, "%H:%M:%S") << " [" << local_time->tm_zone << "]";
    return ss.str();
}


void onCrossTrade(const std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo> &rCrossTrade) {
    std::lock_guard lLock(gCrossTradeMtx);
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

    //API Key
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
    std::cout << "Will stream " << lTickerList.size() << " tickers." << std::endl;

    //Build subscription strings and send to backend
    std::string lCurrentSubscriptionString;
    uint64_t lSubscriptionCounter = 0;
    std::vector<std::unique_ptr<MLinkStreamHandler>> lMLinkStreams;
    for (const auto &rTickerName: lTickerList) {
        auto lSubscriptionCandidate = "ticker.tk:eq:" + rTickerName;
        if (lCurrentSubscriptionString.size() + lSubscriptionCandidate.size() + 3 < 10000) {
            lCurrentSubscriptionString += lSubscriptionCandidate + " | ";
        } else {
            lCurrentSubscriptionString.erase(lCurrentSubscriptionString.size() - 3, 3);
            std::cout << "subscription string: " << lCurrentSubscriptionString << std::endl;
            std::cout <<  "string length: " << lCurrentSubscriptionString.size() << std::endl;

            auto lMLinkStream = std::make_unique<MLinkStreamHandler>();
            lMLinkStream->startStream(lSpiderRockKey, lCurrentSubscriptionString, onCrossTrade);
            lMLinkStreams.push_back(std::move(lMLinkStream));

            lSubscriptionCounter++;
            lCurrentSubscriptionString = lSubscriptionCandidate + " | ";
        }
    }

    if (lCurrentSubscriptionString.size() > 3) {
        lCurrentSubscriptionString.erase(lCurrentSubscriptionString.size() - 3, 3);
        std::cout << "last Subscription string: " << lCurrentSubscriptionString << std::endl;
        std::cout <<  "string length: " << lCurrentSubscriptionString.size() << std::endl;

        auto lMLinkStream = std::make_unique<MLinkStreamHandler>();
        lMLinkStream->startStream(lSpiderRockKey, lCurrentSubscriptionString, onCrossTrade);
        lMLinkStreams.push_back(std::move(lMLinkStream));

        lSubscriptionCounter++;
    }

    std::cout << "used " << lSubscriptionCounter << " connections." << std::endl;

    //detach a thread printing the global debug counters
    std::thread ([&lMLinkStreams]() {
        while (true) {
            //sleep for 10 seconds
            std::this_thread::sleep_for(std::chrono::seconds(10));

            uint64_t lNumberPrintMessages = 0;
            for (const auto &rMLinkStream: lMLinkStreams) {
                lNumberPrintMessages += rMLinkStream->mObserver.mNumberPrintMessages;
            }

            std::cout << "(time: " << getCurrentTime()
                << ") open cross trades: " << gOpenCrossTrades
                << " close cross trades: " << gCloseCrossTrades
                << " unique open: " << gUniqueOpenCross.size()
                << " unique close: " << gUniqueCloseCross.size()
                << " no. print messages: " << lNumberPrintMessages
                << std::endl;
        }
    }).detach();

    //Never exit
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return EXIT_SUCCESS;
}
