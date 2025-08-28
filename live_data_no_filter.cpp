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

std::map<std::string, bool> gTickerListMap;

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
    if (gTickerListMap.count(rCrossTrade->mTicker) == 0) {
        return; //ticker not in the list
    }
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
    std::cout << "Will filter out " << lTickerList.size() << " tickers in the callback." << std::endl;

    //convert the list lTickerList to a map with a bool value placeholder to sort the list alphabetically

    for (const auto &rTickerName: lTickerList) {
        gTickerListMap[rTickerName] = false;
    }

    //Build subscription strings and send to backend
    auto lMLinkStream = std::make_unique<MLinkStreamHandler>();
    lMLinkStream->startStream(lSpiderRockKey, "", onCrossTrade, false);

    //detach a thread printing the global debug counters
    std::thread ([&lMLinkStream]() {
        uint64_t lMinuteCounter = 0;
        while (true) {
            //sleep for 10 seconds
            std::this_thread::sleep_for(std::chrono::seconds(10));

            lMinuteCounter++;

            uint64_t lNumberPrintMessages = lMLinkStream->mObserver.mNumberPrintMessages;

            std::cout << "(time: " << getCurrentTime()
                << ") open cross trades: " << gOpenCrossTrades
                << " close cross trades: " << gCloseCrossTrades
                << " unique open: " << gUniqueOpenCross.size()
                << " unique close: " << gUniqueCloseCross.size()
                << " no. print messages: " << lNumberPrintMessages
                << std::endl;

            //save a file named open_trades.txt containing all lUniqueOpenCrosses contained ticker names sorted in alphabetic order every minute (and the same for close)
            if (lMinuteCounter == 6) {
                lMinuteCounter = 0;
                std::ofstream lTradesFile;
                lTradesFile.open ("open_trades.txt");
                {
                    std::lock_guard lLock(gCrossTradeMtx);
                    for (auto &rUniqueOpenCross : gUniqueOpenCross) {
                        lTradesFile << rUniqueOpenCross.first << std::endl;
                    }
                }
                lTradesFile.close();
                //same for close trades
                lTradesFile.open ("close_trades.txt");
                {
                    std::lock_guard lLock(gCrossTradeMtx);
                    for (auto &rUniqueCloseCross : gUniqueCloseCross) {
                        lTradesFile << rUniqueCloseCross.first << std::endl;
                    }
                }
                lTradesFile.close();
            }
        }
    }).detach();

    //Never exit
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return EXIT_SUCCESS;
}
