//
// Created by Anders Cedronius on 2025-07-11.
//

#include "MLinkStreamHandler.h"

int MLinkStreamHandler::startStream(const std::string& rSpiderRockKey,
    const std::string& rClause,
    const std::function<void(std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo>)>& rCrossTradeCallback,
    const bool aDumpPrintMessage
    ) {

    //Start of Spiderrocks example code from their Github-repo
    //Got no clue about the first 'rest session' part. it's original fails added port 443 then at least the code continues

    //Start of the web socket part (Connect)

    mWebSocketSession = std::make_unique<spiderrock::mlink::MLinkSession>(mContext);

    bool result = mWebSocketSession->connect("wss://mlink-live.nms.saturn.spiderrockconnect.com/mlink/proto", rSpiderRockKey);

    if (!result) {
        result = mWebSocketSession->connect("ws://mlink.saturn.srplatform.net:6700/mlink/proto", rSpiderRockKey);
        if (!result) {
            std::cout << mWebSocketSession->getLastError() << std::endl;
            exit(-1);
        }
    }

    //generate the handlers
    mSubscriptionManager = std::make_unique<spiderrock::mlink::SubscriptionManager<>>(*mWebSocketSession);

    //This callback traverses the incoming data
    //the data is feed the observer got callbacks for stockprint ending up in the method 'onCrossTrade' above

    mSubscriptionManager->start([&](char *buffer, size_t bytesRead) {
            if (buffer[0] == '\r' && buffer[1] == '\n') {
                if (buffer[2] == 'P') {
                    mObserver.process_buffer(buffer, static_cast<int>(bytesRead));
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

    mObserver.mMLinkStreamCheckPtCallback = [&lStreamState, &lStreamCompleted](std::unique_ptr<spiderrock::protobuf::api::Observer::StreamData> pStrmData) {
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
    mObserver.mCrossTradeCallback = rCrossTradeCallback;
    mObserver.mDumpPrints = aDumpPrintMessage;

    //Set up the stream basics
    int activeLatency = 1;
    std::string messageType = "StockPrint";
    std::string queryString = messageType + "_Query";
    spiderrock::protobuf::api::MLinkStream mlinkStream;
    mlinkStream.set_active_latency(activeLatency);
    mlinkStream.set_msg_name(messageType);
    mlinkStream.set_query_label(queryString);
    if (!rClause.empty()) {
        mlinkStream.set_where_clause(rClause);
    }
    mSubscriptionManager->stream(mlinkStream);

    uint64_t lTimeout = 5000; //5 seconds timeout
    while (!lStreamCompleted) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (!lTimeout--) {
            std::cout << "Subscribe string: " << rClause << std::endl;
            throw std::runtime_error("Timeout waiting for stream response");
        }
    }

    return 0;

}