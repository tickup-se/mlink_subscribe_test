//
// Created by Anders Cedronius on 2025-07-11.
//

#pragma once
#include <iostream>
#include "spiderrock_mlink.hpp"
#include "spiderrock_protobuf.hpp"
class MLinkStreamHandler {
    spiderrock::mlink::Context mContext;
    std::unique_ptr<spiderrock::mlink::SubscriptionManager<>> mSubscriptionManager;
    std::unique_ptr<spiderrock::mlink::MLinkSession> mWebSocketSession;
public:

    enum class StreamType: uint8_t {
        Unknown = 0,
        StockPrint = 1,
        StockPrintSet = 2,
    };

    int startStream(const std::string& rSpiderRockKey,
        const std::string& rClause,
        const std::function<void(std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo>)>& rCrossTradeCallback,
        bool aDumpPrintMessage,
        StreamType aStreamType = StreamType::Unknown
        );
    //int stopStream();

    //std::function<void(std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo>)> mCrossTradeCallback = nullptr;

    spiderrock::protobuf::api::Observer mObserver;
};


