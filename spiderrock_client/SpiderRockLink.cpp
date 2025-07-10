//
// Created by Anders Cedronius on 2025-04-24.
//

#include "SpiderRockLink.h"
#include "spiderrock_mlink.hpp"
#include "spiderrock_protobuf_tickup.hpp"

//Global private variables
spiderrock::mlink::SubscriptionManager<> *gMgr = nullptr;

//function to print current time in HH:MM:SS format
void SpiderRockLink::printCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);
    std::cout << "Current time: " << std::put_time(local_time, "%H:%M:%S") << std::endl;
}

bool SpiderRockLink::disconnect() {
    if (gMgr) {
        gMgr->stop();
        gMgr = nullptr;
    } else {
        return false;
    }
    return true;
}

bool SpiderRockLink::subscribe(const std::string& rKey, const std::vector<SubscriptionObjects> &rSubscriptionObjects) {
    if (gMgr) {
        std::cout << "Subscribing already, can't start a new stream."<< std::endl;
        return false;
    }
    std::vector<char> lBuffer(65536 + 1, 0);
    bool lResult = false;

    spiderrock::mlink::Context context;
    spiderrock::mlink::MLinkSession lRestSession(context);

    lResult = lRestSession.connect(
        "https://mlink-live.nms.saturn.spiderrockconnect.com:443/rest/jsonf?cmd=getmsgtypes&where=mToken:ne:SystemData",
        rKey);

    if (!lResult) {
        lResult = lRestSession.connect(
            "http://mlink.saturn.srplatform.net:6700/rest/jsonf?cmd=getmsgtypes&where=mToken:ne:SystemData", rKey);
        if (!lResult) {
            std::cout << lRestSession.getLastError() << std::endl;
            return EXIT_FAILURE;
        }
    }

    int bytesRead = lRestSession.read(lBuffer.data(), lBuffer.size());
    while (bytesRead > 0) {
        lBuffer[bytesRead] = 0;
        std::cout << lBuffer.data();
        bytesRead = lRestSession.read(lBuffer.data(), lBuffer.size());
    }
    lRestSession.close();
    std::cout << std::endl;

    spiderrock::mlink::MLinkSession lWebSocketSession(context);
    lResult = lWebSocketSession.connect("wss://mlink-live.nms.saturn.spiderrockconnect.com/mlink/proto", rKey);
    if (!lResult) {
        std::cout << "error: " << lWebSocketSession.getErrorString() << std::endl;
        return false;
    }

    spiderrock::mlink::SubscriptionManager<> lSubscriptionManager(lWebSocketSession);
    gMgr = &lSubscriptionManager; //Save the global handle

    spiderrock::protobuf::api::Observer lObserver;
    if (mImbalanceCallback) {
        lObserver.mImbalanceCallback = mImbalanceCallback;
        std::cout << "Imbalance callback set" << std::endl;
    }
    if (mMinuteBarCallback) {
        lObserver.mMinuteBarCallback = mMinuteBarCallback;
        std::cout << "Minute bar callback set" << std::endl;
    }
    if (mCrossTradeCallback) {
        lObserver.mCrossTradeCallback = mCrossTradeCallback;
        std::cout << "Cross trade callback set" << std::endl;
    }

    std::atomic<bool> lGotSubAckData = false;
    std::string lSubAckString;
    spiderrock::protobuf::api::SubscribeMsgResult lSubAckResult;

    lObserver.mSubscribeAckCallback = [&lSubAckString, &lSubAckResult, &lGotSubAckData](std::unique_ptr<spiderrock::protobuf::api::Observer::SubscribeData> pSubData) {
        lSubAckString = pSubData->mSubscribeString;
        lSubAckResult = pSubData->mResult;
        lGotSubAckData = true;
    };

    lSubscriptionManager.start([&lObserver](char* buffer, size_t bytesRead)
        {
            if (buffer[0] == '\r' && buffer[1] == '\n') {
                if (buffer[2] == 'P') {
                    lObserver.process_buffer(buffer, static_cast<int>(bytesRead));
                }
                else {
                    buffer[bytesRead] = 0;
                    std::cout << buffer << std::endl;
                }
            }
            else {
                buffer[bytesRead] = 0;
                std::cout << buffer << std::endl;
            }
        }
    );

    uint64_t lSuccessfulSubscriptions = 0;
    std::vector<std::string> lNonSuccessfulInstruments;

    const auto lTimeNow = std::chrono::system_clock::now();
    std::string lDateNow = std::format("{:%Y-%m-%d}", lTimeNow);

    bool lResetFirst = true; //Reset the first subscription
    for (const auto& rSubscriptionObject : rSubscriptionObjects) {
        bool lIsImbalanceOpen = false;
        bool lIsImbalanceClose = false;
        std::string lAuctionTimeString;
        char lTopic[64];
        memset(lTopic, 0, sizeof(lTopic));
        if (rSubscriptionObject.mTopic == SpiderRockLink::MinuteBars) {
            std::strcpy(lTopic, "StockMinuteBar");
        } else if (rSubscriptionObject.mTopic == SpiderRockLink::ImbalanceOpen) {
            lIsImbalanceOpen = true;
            lAuctionTimeString = "Open";
            std::strcpy(lTopic, "StockExchImbalanceV2");
        } else if (rSubscriptionObject.mTopic == SpiderRockLink::ImbalanceClose) {
            lIsImbalanceClose = true;
            lAuctionTimeString = "Closing";
            std::strcpy(lTopic, "StockExchImbalanceV2");
        } else if (rSubscriptionObject.mTopic == SpiderRockLink::Print) {
            std::strcpy(lTopic, "StockPrint");
        } else {
            std::cout << "Unknown topic" << std::endl;
            continue;
        }

        std::cout << "Subscribing to: " << rSubscriptionObject.mInstruments.size() << " instruments for topic: " << lTopic << " ";
        printCurrentTime();

        for (const auto& rInstrumet: rSubscriptionObject.mInstruments) {
            std::string lInstrumentType;
            if (rInstrumet.mType == SpiderRockLink::UnknownInstrument) {
                throw std::runtime_error("Unknown instrument type");
            } else if (rInstrumet.mType == SpiderRockLink::Stock) {
                lInstrumentType = "EQT";
            } else if (rInstrumet.mType == SpiderRockLink::Option) {
                throw std::runtime_error("Option instruments are not supported in this context");
            } else if (rInstrumet.mType == SpiderRockLink::Future) {
                throw std::runtime_error("Future instruments are not supported in this context");
            } else if (rInstrumet.mType == SpiderRockLink::Indices) {
                lInstrumentType = "IDX";
            } else {
                throw std::runtime_error("Unknown instrument type");
            }
            //char lPkey[64] = "VIX-NMS-IDX";
            std::vector<spiderrock::mlink::SubscriptionManager<>::SubscriptionMessage> lSubscriptionMessages;
            char lPkey[64];
            memset(lPkey, 0, sizeof(lPkey));
            if (lIsImbalanceOpen) {
                std::snprintf(lPkey, sizeof(lPkey), "%s-NMS-%s|%s 13:30:00.000000|Market|NYSE", rInstrumet.mName.c_str(), lInstrumentType.c_str(), lDateNow.c_str());
            } else if (lIsImbalanceClose) {
                std::snprintf(lPkey, sizeof(lPkey), "%s-NMS-%s|%s 20:00:00.000000|Market|NYSE", rInstrumet.mName.c_str(), lInstrumentType.c_str(), lDateNow.c_str());
            } else {
                std::snprintf(lPkey, sizeof(lPkey), "%s-NMS-%s", rInstrumet.mName.c_str(), lInstrumentType.c_str());
            }
            lSubscriptionMessages.emplace_back(
                lTopic,
                lPkey,
                "",
                "",
                true
            );
            lSubscriptionManager.subscribe(std::move(lSubscriptionMessages), 1, lResetFirst);
            lResetFirst = false; //Only reset the first subscription
            //wait for the subscribe ack
            uint64_t lTimeout = 5000; //5 seconds timeout
            while (!lGotSubAckData) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                if (!lTimeout--) {
                    throw std::runtime_error("Timeout waiting for subscription response");
                }
            }
            if (lPkey != lSubAckString) {
                throw std::runtime_error("Wrong subscription ack response");
            }
            if (lSubAckResult == spiderrock::protobuf::api::SubscribeMsgResult::SUBSCRIBEMSGRESULT_OK) {
                lSuccessfulSubscriptions++;
            } else {
                lNonSuccessfulInstruments.push_back(rInstrumet.mName + " (" + lTopic + ")");
            }
            lGotSubAckData = false; //Reset the flag for the next subscription
        }
    }

    std::cout << "Successfully subscribed to " << lSuccessfulSubscriptions << " instruments." << std::endl;
    //Print the failing subscriptions
    if (!lNonSuccessfulInstruments.empty()) {
        std::cout << "Failed to subscribe to the following instruments: " << std::endl;
        for (const auto& rInstrument : lNonSuccessfulInstruments) {
            std::cout << rInstrument << std::endl;
        }
    }

    std::cout << "Service start (subscribe): ";
    printCurrentTime();


    std::cout << "service started: ";
    printCurrentTime();
    lSubscriptionManager.join();

    std::cout << "Service joined: ";
    printCurrentTime();
    lSubscriptionManager.shutDown();

    std::cout << "Service shutdown: ";
    printCurrentTime();

    gMgr = nullptr;

    lWebSocketSession.cleanup();


    return true;
}

bool SpiderRockLink::stream(const std::string& rKey, const std::vector<SubscriptionObjects> &rSubscriptionObjects) {
    if (gMgr) {
        std::cout << "Already connected, cannot start a new stream."<< std::endl;
        return false;
    }
    std::vector<char> lBuffer(65536+1);
    spiderrock::mlink::Context lContext;
    spiderrock::mlink::MLinkSession rest_session(lContext);
    if (bool result = rest_session.connect("https://mlink-live.nms.saturn.spiderrockconnect.com:443/rest/jsonf?cmd=getmsgtypes&where=mToken:ne:SystemData", rKey); !result) {
        result = rest_session.connect("http://mlink.saturn.srplatform.net:6700/rest/jsonf?cmd=getmsgtypes&where=mToken:ne:SystemData", rKey);
        if (!result) {
            return false;
        }
    }
    int bytesRead = rest_session.read(lBuffer.data(), lBuffer.size());
    while (bytesRead > 0) {
        lBuffer[bytesRead] = 0;
        //std::cout << lBuffer.data();
        bytesRead = rest_session.read(lBuffer.data(), lBuffer.size());
    }
    rest_session.close();
    //std::cout << std::endl;

    spiderrock::mlink::MLinkSession ws_session(lContext);
    bool lResult = ws_session.connect("wss://mlink-live.nms.saturn.spiderrockconnect.com/mlink/proto", rKey);
    if (!lResult) {
        std::cout << "error: " << ws_session.getErrorString() << std::endl;
        return false;
    }

    spiderrock::mlink::SubscriptionManager<> mgr(ws_session);
    gMgr = &mgr; //Save the global handle

    spiderrock::protobuf::api::Observer lObserver;
    if (mImbalanceCallback) {
        lObserver.mImbalanceCallback = mImbalanceCallback;
        //std::cout << "Imbalance callback set" << std::endl;
    }
    if (mMinuteBarCallback) {
        lObserver.mMinuteBarCallback = mMinuteBarCallback;
        //std::cout << "Minute bar callback set" << std::endl;
    }
    if (mCrossTradeCallback) {
        lObserver.mCrossTradeCallback = mCrossTradeCallback;
        //std::cout << "Cross trade callback set" << std::endl;
    }

    mgr.start([&lObserver](char* buffer, size_t bytesRead)
        {
            if (buffer[0] == '\r' && buffer[1] == '\n') {
                if (buffer[2] == 'P') {
                    lObserver.process_buffer(buffer, static_cast<int>(bytesRead));
                }
                else {
                    buffer[bytesRead] = 0;
                    std::cout << buffer << std::endl;
                }
            }
            else {
                buffer[bytesRead] = 0;
                std::cout << buffer << std::endl;
            }
        }
    );

    //std::string lSubscribeToInstruments;
    //for (int i=0; i < rInstruments.size(); i++) {
    //    if (i == rInstruments.size()-1) {
    //        lSubscribeToInstruments += "ticker.tk:eq:" + rInstruments[i];
    //    } else {
    //        lSubscribeToInstruments += "ticker.tk:eq:" + rInstruments[i] + " | ";
    //    }
    //}

    uint64_t lStreamState = 0;
    std::atomic<bool> lStreamCompleted= false;

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

    uint64_t lStreamCounter  = 0;

    spiderrock::protobuf::api::MLinkStream  mlinkStream;
    mlinkStream.set_active_latency(1);
    for (const auto& rSubscriptionObject : rSubscriptionObjects) {
        std::string lTopic;
        if (rSubscriptionObject.mTopic == SpiderRockLink::MinuteBars) {
            lTopic = "StockMinuteBar";
        } else if (rSubscriptionObject.mTopic == SpiderRockLink::Imbalance) {
            lTopic = "StockExchImbalanceV2";
        } else if (rSubscriptionObject.mTopic == SpiderRockLink::Print) {
            lTopic = "StockPrint";
        } else {
            std::cout << "Unknown topic" << std::endl;
            continue;
        }
        mlinkStream.set_msg_name(lTopic);
        mlinkStream.set_query_label( lTopic + "_Query");
        std::string lSubscribeToInstruments;
        uint64_t lBreakCount = 0;
        uint64_t lSubStreamCounter  = 0;
        for (const auto& rInstrumet: rSubscriptionObject.mInstruments) {
            lSubscribeToInstruments += "ticker.tk:eq:" + rInstrumet.mName;
            lSubStreamCounter++;
            lBreakCount++;
            if (lBreakCount > 50) {
                mlinkStream.set_where_clause(lSubscribeToInstruments);
                mgr.stream(mlinkStream);
                lSubscribeToInstruments = "";
                lBreakCount = 0;

                uint64_t lTimeout = 5000; //5 seconds timeout
                while (!lStreamCompleted) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    if (!lTimeout--) {
                        std::cout << "topic: " << lTopic << std::endl;
                        std::cout << "subscribe string: " << lSubscribeToInstruments << std::endl;
                        throw std::runtime_error("timeout waiting for stream response");
                    }
                }
                lStreamCompleted = false;

            } else {
                lSubscribeToInstruments += " | ";
            }
        }

        if (!lSubscribeToInstruments.empty()) {
            //Remove the last three characters from the string lSubscribeToInstruments to remove the last " | "
            lSubscribeToInstruments.erase(lSubscribeToInstruments.size() - 3, 3);
            mlinkStream.set_where_clause(lSubscribeToInstruments);
            mgr.stream(mlinkStream);

            uint64_t lTimeout = 5000; //5 seconds timeout
            while (!lStreamCompleted) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                if (!lTimeout--) {
                    std::cout << "topic: " << lTopic << std::endl;
                    std::cout << "Subscribe string: " << lSubscribeToInstruments << std::endl;
                    throw std::runtime_error("Timeout waiting for stream response");
                }
            }
            lStreamCompleted = false;
        }
        std::cout << "topic: " << lTopic << " subscribed to: " << lSubStreamCounter << " instruments" << std::endl;
        lStreamCounter += lSubStreamCounter;
    }
    std::cout << "Stream completed for a total of: " << lStreamCounter << " instruments" << std::endl;

    //mlinkStream.set_where_clause("ticker.tk:eq:MMM | ticker.tk:eq:AXP | ticker.tk:eq:XYZX");
    //mlinkStream.set_where_clause("");



    //std::cout << "Service start (stream): ";
    //printCurrentTime();
    //mgr.stream(mlinkStream);

    std::cout << "service started: ";
    printCurrentTime();
    mgr.join();

    std::cout << "Service joined: ";
    printCurrentTime();
    mgr.shutDown();

    std::cout << "Service shutdown: ";
    printCurrentTime();

    gMgr = nullptr;

    ws_session.cleanup();
    return true;
}
