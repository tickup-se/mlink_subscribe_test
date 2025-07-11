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
    int startStream(const std::string& rSpiderRockKey,
        const std::string& rClause,
        const std::function<void(std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo>)>& rCrossTradeCallback);
    //int stopStream();

    //std::function<void(std::unique_ptr<spiderrock::protobuf::api::Observer::CrossTradeInfo>)> mCrossTradeCallback = nullptr;

    spiderrock::protobuf::api::Observer mObserver;
};


