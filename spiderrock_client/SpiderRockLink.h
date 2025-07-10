//
// Created by Anders Cedronius on 2025-04-24.
//

#pragma once

#include <iostream>


#include "tickup/spiderrockbroker/v1/spiderrockbroker_api.pb.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>


class SpiderRockLink {
public:

    enum MLinkTopic {
        UnknownTopic = 0,
        MinuteBars,
        Imbalance, //Stream interface only
        ImbalanceOpen,
        ImbalanceClose,
        Print //Trades
    };

    enum MLinkInstrumentType {
        UnknownInstrument = 0,
        Stock,
        Option,
        Future,
        Indices
    };

    struct Instrument {
        std::string mName;
        MLinkInstrumentType mType = UnknownInstrument;
    };

    struct SubscriptionObjects
    {
        MLinkTopic mTopic;
        std::vector<Instrument> mInstruments;
    };

    //The stream interface is capable of streaming a topic from the MLink backend
    bool stream(const std::string& rKey, const std::vector<SubscriptionObjects> &rSubscriptionObjects);
    [[deprecated("subscribe is deprecated and should not be used")]]
    bool subscribe(const std::string& rKey, const std::vector<SubscriptionObjects> &rSubscriptionObjects);
    static bool disconnect();
    static void printCurrentTime();
    std::function<void(std::unique_ptr<tickup::spiderrockbroker::v1::SpiderRockImbalance>)> mImbalanceCallback;
    std::function<void(std::unique_ptr<tickup::spiderrockbroker::v1::SpiderRockMinuteBar>)> mMinuteBarCallback;
    std::function<void(std::unique_ptr<tickup::spiderrockbroker::v1::SpiderRockCrossTrade>)> mCrossTradeCallback;



};
