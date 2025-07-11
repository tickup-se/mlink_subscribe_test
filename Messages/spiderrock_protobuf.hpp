#pragma once

/*
                std::ostream *o = &std::cout;
                *o << msgMLinkStreamAck;
 */


#include <ostream>
#include <iostream>
#include <google/protobuf/util/time_util.h>

#include "spiderrock_protobuf_base.hpp"

#include "spiderrock_common.hpp"
#include "ClientControl/AccountRouteConfig.hpp"
#include "ClientControl/AltSymbolMap.hpp"
#include "ClientControl/AssetAccountControl.hpp"
#include "ClientControl/AvailableStockLocates.hpp"
#include "ClientControl/BookControl.hpp"
#include "ClientControl/ClientAccntStrategyMap.hpp"
#include "ClientControl/ClientAccountConfig.hpp"
#include "ClientControl/ClientStockLocate.hpp"
#include "ClientControl/CustomControl.hpp"
#include "ClientControl/ExpirationControl.hpp"
#include "ClientControl/FutureControl.hpp"
#include "ClientControl/GlobalRiskControl.hpp"
#include "ClientControl/IndustryControl.hpp"
#include "ClientControl/MarRiskComposite.hpp"
#include "ClientControl/MarRiskControl.hpp"
#include "ClientControl/MarRiskControlTkOverride.hpp"
#include "ClientControl/MarRiskCounter.hpp"
#include "ClientControl/RiskClassControl.hpp"
#include "ClientControl/SectorControl.hpp"
#include "ClientControl/SpdrRiskControl.hpp"
#include "ClientControl/SpdrRiskCounter.hpp"
#include "ClientControl/StockLocateRequest.hpp"
#include "ClientControl/StockLocateResponse.hpp"
#include "ClientControl/StockPoolBorrowRate.hpp"
#include "ClientControl/StockThreshold.hpp"
#include "ClientControl/SymbolControl.hpp"
#include "ClientControl/UserDividendOverride.hpp"
#include "ClientControl/UserRateOverride.hpp"
#include "ClientLive/IndexQuote.hpp"
#include "ClientLive/MarketHoursConfig.hpp"
#include "ClientLive/NMSCircuitBreaker.hpp"
#include "ClientLive/OpraPrintType.hpp"
#include "ClientLive/OptionEOP.hpp"
#include "ClientLive/OptionOpenAuction.hpp"
#include "ClientLive/OptionOpenAuctionSummary.hpp"
#include "ClientLive/OptionPrint2.hpp"
#include "ClientLive/OptionPrintSummary.hpp"
#include "ClientLive/OptionSettlementMark.hpp"
#include "ClientLive/ProductPriceBand.hpp"
#include "ClientLive/ProductTradingStatus.hpp"
#include "ClientLive/ProductTradingStatusV2.hpp"
#include "ClientLive/RFQQuoteBroadcast.hpp"
#include "ClientLive/SOQConstituentSymbolMap.hpp"
#include "ClientLive/SOQStrikeRangeUpdate.hpp"
#include "ClientLive/StockAuctionSummary.hpp"
#include "ClientLive/StockExchImbalance.hpp"
#include "ClientLive/StockImbalance.hpp"
#include "ClientLive/StockRegSHOStatus.hpp"
#include "ClientLive/SyntheticExpiryQuote.hpp"
#include "ClientLive/SyntheticFutureQuote.hpp"
#include "ClientRisk/AccountRiskRecordV5.hpp"
#include "ClientRisk/ClientBeta.hpp"
#include "ClientRisk/CurrencyPositionRecordV5.hpp"
#include "ClientRisk/CurrencyTransaction.hpp"
#include "ClientRisk/EquityCorpActionRecordV5.hpp"
#include "ClientRisk/ExpirationRiskRecordV5.hpp"
#include "ClientRisk/FuturePositionRecordV5.hpp"
#include "ClientRisk/FutureRiskDetailV5.hpp"
#include "ClientRisk/FutureRiskSummaryV5.hpp"
#include "ClientRisk/IndustryRiskRecordV5.hpp"
#include "ClientRisk/OptionCorpActionRecordV5.hpp"
#include "ClientRisk/OptionExAsRecordV5.hpp"
#include "ClientRisk/OptionPositionRecordV5.hpp"
#include "ClientRisk/ProductRiskDetailV5.hpp"
#include "ClientRisk/ProductRiskSummaryV5.hpp"
#include "ClientRisk/RiskAggGroupStateV5.hpp"
#include "ClientRisk/RiskCubeDetailV5.hpp"
#include "ClientRisk/SodCashRecordV5.hpp"
#include "ClientRisk/SodClearingRecordV5.hpp"
#include "ClientRisk/StockPositionRecordV5.hpp"
#include "ClientRisk/SymbolMarginSummaryV5.hpp"
#include "ClientRisk/SymbolRiskDetailV5.hpp"
#include "ClientRisk/SymbolRiskSummaryV5.hpp"
#include "ClientRisk/TradeCubeDetailV5.hpp"
#include "ClientTheo/OptionTheoVol.hpp"
#include "ClientTheo/SpdrOptTheoRecord.hpp"
#include "ClientTheo/SpdrTheoExp2PtCurve.hpp"
#include "ClientTheo/SpdrTheoExpSurface.hpp"
#include "ClientTheo/TheoSurfacePerf.hpp"
#include "ClientTrading/AutoHedgeSymbol.hpp"
#include "ClientTrading/ExternAggGroupReport.hpp"
#include "ClientTrading/RiskGroupCounter.hpp"
#include "ClientTrading/SpdrAccntCancel.hpp"
#include "ClientTrading/SpdrAllocationNotice.hpp"
#include "ClientTrading/SpdrAllocationNoticeStatus.hpp"
#include "ClientTrading/SpdrAutoHedgeControl.hpp"
#include "ClientTrading/SpdrAutoHedgeState.hpp"
#include "ClientTrading/SpdrAvailExecAllocation.hpp"
#include "ClientTrading/SpdrAwayExecution.hpp"
#include "ClientTrading/SpdrBrokerCancel.hpp"
#include "ClientTrading/SpdrClientFirmRiskMgmt.hpp"
#include "ClientTrading/SpdrDropExecution.hpp"
#include "ClientTrading/SpdrDropExecutionAck.hpp"
#include "ClientTrading/SpdrExchRiskDrop.hpp"
#include "ClientTrading/SpdrExchRiskMgmt.hpp"
#include "ClientTrading/SpdrExchRiskReset.hpp"
#include "ClientTrading/SpdrExecutionAllocation.hpp"
#include "ClientTrading/SpdrExecutionAllocationStatus.hpp"
#include "ClientTrading/SpdrMLegBrkrEvent.hpp"
#include "ClientTrading/SpdrMLegBrkrState.hpp"
#include "ClientTrading/SpdrOmniOrder.hpp"
#include "ClientTrading/SpdrParentAllocation.hpp"
#include "ClientTrading/SpdrParentAllocationStatus.hpp"
#include "ClientTrading/SpdrParentBrkrEvent.hpp"
#include "ClientTrading/SpdrParentBrkrState.hpp"
#include "ClientTrading/SpdrParentBrokerSummary.hpp"
#include "ClientTrading/SpdrParentCancel.hpp"
#include "ClientTrading/SpdrParentExecution.hpp"
#include "ClientTrading/SpdrParentLimit.hpp"
#include "ClientTrading/SpdrParentOrder.hpp"
#include "ClientTrading/SpdrParentReport.hpp"
#include "ClientTrading/SpdrParentReviewRequest.hpp"
#include "ClientTrading/SpdrParentReviewResponse.hpp"
#include "ClientTrading/SpdrReleaseWaitTrigger.hpp"
#include "ClientTrading/SpdrRiskExecution.hpp"
#include "ClientTrading/SpdrRiskGroupCancel.hpp"
#include "ClientTrading/SpdrRiskGroupControl.hpp"
#include "ClientTrading/SpdrRouteCancel.hpp"
#include "ClientTrading/SpdrSecKeyCancel.hpp"
#include "ClientTrading/SpdrSetActiveSize.hpp"
#include "ClientTrading/SpdrStripeTrigger.hpp"
#include "ClientTrading/SpdrSweepDetail.hpp"
#include "ClientTrading/SpdrSweepExchDetail.hpp"
#include "ClientTrading/SpdrUserCancel.hpp"
#include "ClientTrading/ToolCompositeExecution.hpp"
#include "EqtAnalytics/StockBetaExt.hpp"
#include "EqtAnalytics/StockEarningsCalendar.hpp"
#include "EqtAnalytics/StockPrintMarkup.hpp"
#include "EqtAnalytics/StockPrintSet.hpp"
#include "EqtAnalytics/TickerAnalytics.hpp"
#include "EqtAnalytics/UserSDivOverride.hpp"
#include "EqtExchImbalance/StockExchImbalanceV2.hpp"
#include "EqtMarkData/StockCloseMark.hpp"
#include "EqtMarkData/StockOpenMark.hpp"
#include "EqtMktData/StockBookQuote.hpp"
#include "EqtMktData/StockPrint.hpp"
#include "EqtSummaryData/StockMarketSummary.hpp"
#include "EqtSummaryData/StockMinuteBar.hpp"
#include "EquityDefinition/RegionalUnderlierComposite.hpp"
#include "EquityDefinition/TickerDefinition.hpp"
#include "EquityDefinition/TickerDefinitionExt.hpp"
#include "FutAnalytics/FuturePrintMarkup.hpp"
#include "FutAnalytics/FuturePrintSet.hpp"
#include "FutMarkData/FutureCloseMark.hpp"
#include "FutMarkData/FutureOpenMark.hpp"
#include "FutMarkData/FutureSettlementMark.hpp"
#include "FutMktData/FutureBookQuote.hpp"
#include "FutMktData/FuturePrint.hpp"
#include "FutProbModel/FuturePrintProbability.hpp"
#include "FutProbModel/FutureQuoteProbability.hpp"
#include "FutSummaryData/FutureMarketSummary.hpp"
#include "FutSummaryData/FutureMinuteBar.hpp"
#include "FutureDefinition/CCodeDefinition.hpp"
#include "FutureDefinition/ProductDefinitionV2.hpp"
#include "FxMktData/CurrencyConversion.hpp"
#include "GlobalDefinition/GlobalDividends.hpp"
#include "GlobalDefinition/GlobalRates.hpp"
#include "MLinkRest/AggregateCount.hpp"
#include "MLinkRest/AggregateNumeric.hpp"
#include "MLinkRest/AggregateString.hpp"
#include "MLinkRest/BucketRange.hpp"
#include "MLinkRest/FieldDesc.hpp"
#include "MLinkRest/MLinkCount.hpp"
#include "MLinkRest/MsgDesc.hpp"
#include "MLinkRest/MsgExpiryKey.hpp"
#include "MLinkRest/MsgOptionKey.hpp"
#include "MLinkRest/MsgTickerKey.hpp"
#include "MLinkRest/PostAck.hpp"
#include "MLinkRest/QueryResult.hpp"
#include "MLinkRest/UserApiKey.hpp"
#include "MLinkRest/UserMetaData.hpp"
#include "MLinkWs/MLinkAdmin.hpp"
#include "MLinkWs/MLinkDataAck.hpp"
#include "MLinkWs/MLinkHeartbeat.hpp"
#include "MLinkWs/MLinkLogon.hpp"
#include "MLinkWs/MLinkSignalReady.hpp"
#include "MLinkWs/MLinkStream.hpp"
#include "MLinkWs/MLinkStreamAck.hpp"
#include "MLinkWs/MLinkStreamCheckPt.hpp"
#include "MLinkWs/MLinkSubscribe.hpp"
#include "MLinkWs/MLinkSubscribeAck.hpp"
#include "MLinkWs/MLinkSubscribeCheckPt.hpp"
#include "NationsIndex/NationsIndexPrice.hpp"
#include "OptAnalytics/LiveImpliedQuote.hpp"
#include "OptAnalytics/LiveImpliedQuoteAdj.hpp"
#include "OptAnalytics/LiveImpliedQuoteDisp.hpp"
#include "OptAnalytics/LiveRevConQuote.hpp"
#include "OptAnalytics/OptionPrintSet.hpp"
#include "OptAnalytics/OptionRiskFactor.hpp"
#include "OptAnalytics/StockBeta.hpp"
#include "OptExchAuction/SpdrAuctionState.hpp"
#include "OptionDefinition/OptExpiryDefinition.hpp"
#include "OptionDefinition/RegionalInstrumentId.hpp"
#include "OptionDefinition/RegionalOptionComposite.hpp"
#include "OptionDefinition/RootDefinition.hpp"
#include "OptMarkData/OptionCloseMark.hpp"
#include "OptMarkData/OptionOpenInterest.hpp"
#include "OptMarkData/OptionOpenMark.hpp"
#include "OptMktData/OptionFlexEvent.hpp"
#include "OptMktData/OptionNbboQuote.hpp"
#include "OptMktData/OptionPrint.hpp"
#include "OptProbModel/OptionPrintProbability.hpp"
#include "OptProbModel/OptionQuoteProbability.hpp"
#include "OptSummaryData/OptionMarketSummary.hpp"
#include "OptSurface/HistoricalVolatilities.hpp"
#include "OptSurface/LiveAtmVol.hpp"
#include "OptSurface/LiveSurfaceCurve.hpp"
#include "OptSurface/LiveSurfaceFixedGrid.hpp"
#include "OptSurface/LiveSurfaceFixedTerm.hpp"
#include "OptSurface/OptionAtmMinuteBarData.hpp"
#include "RiskCalc/GetOptionBasket.hpp"
#include "RiskCalc/GetOptionPrice.hpp"
#include "RiskCalc/GetOptionVolatility.hpp"
#include "RiskCalc/OptionItemCalc.hpp"
#include "RiskCalc/OptionItemDef.hpp"
#include "SpreadDefinition/SpreadDefinition.hpp"
#include "SpreadDefinition/SpreadExchDefinition.hpp"
#include "SpreadExchData/SpreadExchOrder.hpp"
#include "SpreadMktData/SpreadBookMarkup.hpp"
#include "SpreadMktData/SpreadBookQuote.hpp"
#include "SpreadMktData/SpreadCloseMark.hpp"
#include "SpreadMktData/SpreadMarketSummary.hpp"
#include "SpreadMktData/SpreadOpenMark.hpp"
#include "SpreadMktData/SpreadPrint.hpp"
#include "SRATS/AuctionNotice.hpp"
#include "SRATS/AuctionNoticeBX.hpp"
#include "SRATS/AuctionNoticeRC.hpp"
#include "SRATS/AuctionNoticeSN.hpp"
#include "SRATS/AuctionPrint.hpp"
#include "SRATS/AuctionPrintBX.hpp"
#include "SRATS/AuctionPrintRC.hpp"
#include "SRATS/AuctionPrintSN.hpp"
#include "SRATS/AuctionState.hpp"
#include "SRATS/AutoResponderBX.hpp"
#include "SRATS/AutoResponderRC.hpp"
#include "SRATS/AutoResponderSN.hpp"
#include "SRATS/AutoResponderVegaDir.hpp"
#include "SRATS/NoticeCancel.hpp"
#include "SRATS/NoticeExecReport.hpp"
#include "SRATS/NoticeResponse.hpp"
#include "SRATS/ResponderMarkupBX.hpp"
#include "SRATS/ResponderMarkupRC.hpp"
#include "SRATS/ResponderMarkupSN.hpp"
#include "SRATS/ResponderMarkupVegaDir.hpp"
#include "SRATS/UserAuctionFilter.hpp"
#include "SRATS/UserAuctionTickerFilter.hpp"
#include "SRMLinkAnalytics/IndustryDefinition.hpp"
#include "SRMLinkAnalytics/LiveBasisCurve.hpp"
#include "SRMLinkAnalytics/LiveExpiryAtm.hpp"
#include "SRMLinkAnalytics/LiveExpirySurface.hpp"
#include "SRMLinkAnalytics/LiveIVarSwapFixedTerm.hpp"
#include "SRMLinkAnalytics/LiveSurfaceAtm.hpp"
#include "SRMLinkAnalytics/LiveSurfacePerf.hpp"
#include "SRMLinkAnalytics/OptionLookback.hpp"
#include "SRMLinkAnalytics/OptionOpenVega.hpp"
#include "SRMLinkAnalytics/OptionPrintSetSummary.hpp"
#include "SRMLinkAnalytics/SpanRiskCalculator.hpp"
#include "SRMLinkAnalytics/StockBorrowRate.hpp"
#include "SRMLinkAnalytics/StockDetail.hpp"
#include "SRMLinkAnalytics/SyntheticExpiryCloseMark.hpp"
#include "SRMLinkAnalytics/SyntheticExpiryOpenMark.hpp"
#include "SRMLinkAnalytics/VolTimeCalculator.hpp"
#include "StkProbModel/StockPrintProbability.hpp"
#include "StkProbModel/StockQuoteProbability.hpp"
#include "WSHCorporateEvent/WshFutureQuarters.hpp"

namespace spiderrock {
namespace protobuf {
namespace api {

class Observer {
    AccountRouteConfig msgAccountRouteConfig{};
    AltSymbolMap msgAltSymbolMap{};
    AssetAccountControl msgAssetAccountControl{};
    AvailableStockLocates msgAvailableStockLocates{};
    BookControl msgBookControl{};
    ClientAccntStrategyMap msgClientAccntStrategyMap{};
    ClientAccountConfig msgClientAccountConfig{};
    ClientStockLocate msgClientStockLocate{};
    CustomControl msgCustomControl{};
    ExpirationControl msgExpirationControl{};
    FutureControl msgFutureControl{};
    GlobalRiskControl msgGlobalRiskControl{};
    IndustryControl msgIndustryControl{};
    MarRiskComposite msgMarRiskComposite{};
    MarRiskControl msgMarRiskControl{};
    MarRiskControlTkOverride msgMarRiskControlTkOverride{};
    MarRiskCounter msgMarRiskCounter{};
    RiskClassControl msgRiskClassControl{};
    SectorControl msgSectorControl{};
    SpdrRiskControl msgSpdrRiskControl{};
    SpdrRiskCounter msgSpdrRiskCounter{};
    StockLocateRequest msgStockLocateRequest{};
    StockLocateResponse msgStockLocateResponse{};
    StockPoolBorrowRate msgStockPoolBorrowRate{};
    StockThreshold msgStockThreshold{};
    SymbolControl msgSymbolControl{};
    UserDividendOverride msgUserDividendOverride{};
    UserRateOverride msgUserRateOverride{};
    IndexQuote msgIndexQuote{};
    MarketHoursConfig msgMarketHoursConfig{};
    NMSCircuitBreaker msgNMSCircuitBreaker{};
    OpraPrintType msgOpraPrintType{};
    OptionEOP msgOptionEOP{};
    OptionOpenAuction msgOptionOpenAuction{};
    OptionOpenAuctionSummary msgOptionOpenAuctionSummary{};
    OptionPrint2 msgOptionPrint2{};
    OptionPrintSummary msgOptionPrintSummary{};
    OptionSettlementMark msgOptionSettlementMark{};
    ProductPriceBand msgProductPriceBand{};
    ProductTradingStatus msgProductTradingStatus{};
    ProductTradingStatusV2 msgProductTradingStatusV2{};
    RFQQuoteBroadcast msgRFQQuoteBroadcast{};
    SOQConstituentSymbolMap msgSOQConstituentSymbolMap{};
    SOQStrikeRangeUpdate msgSOQStrikeRangeUpdate{};
    StockAuctionSummary msgStockAuctionSummary{};
    StockExchImbalance msgStockExchImbalance{};
    StockImbalance msgStockImbalance{};
    StockRegSHOStatus msgStockRegSHOStatus{};
    SyntheticExpiryQuote msgSyntheticExpiryQuote{};
    SyntheticFutureQuote msgSyntheticFutureQuote{};
    AccountRiskRecordV5 msgAccountRiskRecordV5{};
    ClientBeta msgClientBeta{};
    CurrencyPositionRecordV5 msgCurrencyPositionRecordV5{};
    CurrencyTransaction msgCurrencyTransaction{};
    EquityCorpActionRecordV5 msgEquityCorpActionRecordV5{};
    ExpirationRiskRecordV5 msgExpirationRiskRecordV5{};
    FuturePositionRecordV5 msgFuturePositionRecordV5{};
    FutureRiskDetailV5 msgFutureRiskDetailV5{};
    FutureRiskSummaryV5 msgFutureRiskSummaryV5{};
    IndustryRiskRecordV5 msgIndustryRiskRecordV5{};
    OptionCorpActionRecordV5 msgOptionCorpActionRecordV5{};
    OptionExAsRecordV5 msgOptionExAsRecordV5{};
    OptionPositionRecordV5 msgOptionPositionRecordV5{};
    ProductRiskDetailV5 msgProductRiskDetailV5{};
    ProductRiskSummaryV5 msgProductRiskSummaryV5{};
    RiskAggGroupStateV5 msgRiskAggGroupStateV5{};
    RiskCubeDetailV5 msgRiskCubeDetailV5{};
    SodCashRecordV5 msgSodCashRecordV5{};
    SodClearingRecordV5 msgSodClearingRecordV5{};
    StockPositionRecordV5 msgStockPositionRecordV5{};
    SymbolMarginSummaryV5 msgSymbolMarginSummaryV5{};
    SymbolRiskDetailV5 msgSymbolRiskDetailV5{};
    SymbolRiskSummaryV5 msgSymbolRiskSummaryV5{};
    TradeCubeDetailV5 msgTradeCubeDetailV5{};
    OptionTheoVol msgOptionTheoVol{};
    SpdrOptTheoRecord msgSpdrOptTheoRecord{};
    SpdrTheoExp2PtCurve msgSpdrTheoExp2PtCurve{};
    SpdrTheoExpSurface msgSpdrTheoExpSurface{};
    TheoSurfacePerf msgTheoSurfacePerf{};
    AutoHedgeSymbol msgAutoHedgeSymbol{};
    ExternAggGroupReport msgExternAggGroupReport{};
    RiskGroupCounter msgRiskGroupCounter{};
    SpdrAccntCancel msgSpdrAccntCancel{};
    SpdrAllocationNotice msgSpdrAllocationNotice{};
    SpdrAllocationNoticeStatus msgSpdrAllocationNoticeStatus{};
    SpdrAutoHedgeControl msgSpdrAutoHedgeControl{};
    SpdrAutoHedgeState msgSpdrAutoHedgeState{};
    SpdrAvailExecAllocation msgSpdrAvailExecAllocation{};
    SpdrAwayExecution msgSpdrAwayExecution{};
    SpdrBrokerCancel msgSpdrBrokerCancel{};
    SpdrClientFirmRiskMgmt msgSpdrClientFirmRiskMgmt{};
    SpdrDropExecution msgSpdrDropExecution{};
    SpdrDropExecutionAck msgSpdrDropExecutionAck{};
    SpdrExchRiskDrop msgSpdrExchRiskDrop{};
    SpdrExchRiskMgmt msgSpdrExchRiskMgmt{};
    SpdrExchRiskReset msgSpdrExchRiskReset{};
    SpdrExecutionAllocation msgSpdrExecutionAllocation{};
    SpdrExecutionAllocationStatus msgSpdrExecutionAllocationStatus{};
    SpdrMLegBrkrEvent msgSpdrMLegBrkrEvent{};
    SpdrMLegBrkrState msgSpdrMLegBrkrState{};
    SpdrOmniOrder msgSpdrOmniOrder{};
    SpdrParentAllocation msgSpdrParentAllocation{};
    SpdrParentAllocationStatus msgSpdrParentAllocationStatus{};
    SpdrParentBrkrEvent msgSpdrParentBrkrEvent{};
    SpdrParentBrkrState msgSpdrParentBrkrState{};
    SpdrParentBrokerSummary msgSpdrParentBrokerSummary{};
    SpdrParentCancel msgSpdrParentCancel{};
    SpdrParentExecution msgSpdrParentExecution{};
    SpdrParentLimit msgSpdrParentLimit{};
    SpdrParentOrder msgSpdrParentOrder{};
    SpdrParentReport msgSpdrParentReport{};
    SpdrParentReviewRequest msgSpdrParentReviewRequest{};
    SpdrParentReviewResponse msgSpdrParentReviewResponse{};
    SpdrReleaseWaitTrigger msgSpdrReleaseWaitTrigger{};
    SpdrRiskExecution msgSpdrRiskExecution{};
    SpdrRiskGroupCancel msgSpdrRiskGroupCancel{};
    SpdrRiskGroupControl msgSpdrRiskGroupControl{};
    SpdrRouteCancel msgSpdrRouteCancel{};
    SpdrSecKeyCancel msgSpdrSecKeyCancel{};
    SpdrSetActiveSize msgSpdrSetActiveSize{};
    SpdrStripeTrigger msgSpdrStripeTrigger{};
    SpdrSweepDetail msgSpdrSweepDetail{};
    SpdrSweepExchDetail msgSpdrSweepExchDetail{};
    SpdrUserCancel msgSpdrUserCancel{};
    ToolCompositeExecution msgToolCompositeExecution{};
    StockBetaExt msgStockBetaExt{};
    StockEarningsCalendar msgStockEarningsCalendar{};
    StockPrintMarkup msgStockPrintMarkup{};
    StockPrintSet msgStockPrintSet{};
    TickerAnalytics msgTickerAnalytics{};
    UserSDivOverride msgUserSDivOverride{};
    StockExchImbalanceV2 msgStockExchImbalanceV2{};
    StockCloseMark msgStockCloseMark{};
    StockOpenMark msgStockOpenMark{};
    StockBookQuote msgStockBookQuote{};
    StockPrint msgStockPrint{};
    StockMarketSummary msgStockMarketSummary{};
    StockMinuteBar msgStockMinuteBar{};
    RegionalUnderlierComposite msgRegionalUnderlierComposite{};
    TickerDefinition msgTickerDefinition{};
    TickerDefinitionExt msgTickerDefinitionExt{};
    FuturePrintMarkup msgFuturePrintMarkup{};
    FuturePrintSet msgFuturePrintSet{};
    FutureCloseMark msgFutureCloseMark{};
    FutureOpenMark msgFutureOpenMark{};
    FutureSettlementMark msgFutureSettlementMark{};
    FutureBookQuote msgFutureBookQuote{};
    FuturePrint msgFuturePrint{};
    FuturePrintProbability msgFuturePrintProbability{};
    FutureQuoteProbability msgFutureQuoteProbability{};
    FutureMarketSummary msgFutureMarketSummary{};
    FutureMinuteBar msgFutureMinuteBar{};
    CCodeDefinition msgCCodeDefinition{};
    ProductDefinitionV2 msgProductDefinitionV2{};
    CurrencyConversion msgCurrencyConversion{};
    GlobalDividends msgGlobalDividends{};
    GlobalRates msgGlobalRates{};
    AggregateCount msgAggregateCount{};
    AggregateNumeric msgAggregateNumeric{};
    AggregateString msgAggregateString{};
    BucketRange msgBucketRange{};
    FieldDesc msgFieldDesc{};
    MLinkCount msgMLinkCount{};
    MsgDesc msgMsgDesc{};
    MsgExpiryKey msgMsgExpiryKey{};
    MsgOptionKey msgMsgOptionKey{};
    MsgTickerKey msgMsgTickerKey{};
    PostAck msgPostAck{};
    QueryResult msgQueryResult{};
    UserApiKey msgUserApiKey{};
    UserMetaData msgUserMetaData{};
    MLinkAdmin msgMLinkAdmin{};
    MLinkDataAck msgMLinkDataAck{};
    MLinkHeartbeat msgMLinkHeartbeat{};
    MLinkLogon msgMLinkLogon{};
    MLinkSignalReady msgMLinkSignalReady{};
    MLinkStream msgMLinkStream{};
    MLinkStreamAck msgMLinkStreamAck{};
    MLinkStreamCheckPt msgMLinkStreamCheckPt{};
    MLinkSubscribe msgMLinkSubscribe{};
    MLinkSubscribeAck msgMLinkSubscribeAck{};
    MLinkSubscribeCheckPt msgMLinkSubscribeCheckPt{};
    NationsIndexPrice msgNationsIndexPrice{};
    LiveImpliedQuote msgLiveImpliedQuote{};
    LiveImpliedQuoteAdj msgLiveImpliedQuoteAdj{};
    LiveImpliedQuoteDisp msgLiveImpliedQuoteDisp{};
    LiveRevConQuote msgLiveRevConQuote{};
    OptionPrintSet msgOptionPrintSet{};
    OptionRiskFactor msgOptionRiskFactor{};
    StockBeta msgStockBeta{};
    SpdrAuctionState msgSpdrAuctionState{};
    OptExpiryDefinition msgOptExpiryDefinition{};
    RegionalInstrumentId msgRegionalInstrumentId{};
    RegionalOptionComposite msgRegionalOptionComposite{};
    RootDefinition msgRootDefinition{};
    OptionCloseMark msgOptionCloseMark{};
    OptionOpenInterest msgOptionOpenInterest{};
    OptionOpenMark msgOptionOpenMark{};
    OptionFlexEvent msgOptionFlexEvent{};
    OptionNbboQuote msgOptionNbboQuote{};
    OptionPrint msgOptionPrint{};
    OptionPrintProbability msgOptionPrintProbability{};
    OptionQuoteProbability msgOptionQuoteProbability{};
    OptionMarketSummary msgOptionMarketSummary{};
    HistoricalVolatilities msgHistoricalVolatilities{};
    LiveAtmVol msgLiveAtmVol{};
    LiveSurfaceCurve msgLiveSurfaceCurve{};
    LiveSurfaceFixedGrid msgLiveSurfaceFixedGrid{};
    LiveSurfaceFixedTerm msgLiveSurfaceFixedTerm{};
    OptionAtmMinuteBarData msgOptionAtmMinuteBarData{};
    GetOptionBasket msgGetOptionBasket{};
    GetOptionPrice msgGetOptionPrice{};
    GetOptionVolatility msgGetOptionVolatility{};
    OptionItemCalc msgOptionItemCalc{};
    OptionItemDef msgOptionItemDef{};
    SpreadDefinition msgSpreadDefinition{};
    SpreadExchDefinition msgSpreadExchDefinition{};
    SpreadExchOrder msgSpreadExchOrder{};
    SpreadBookMarkup msgSpreadBookMarkup{};
    SpreadBookQuote msgSpreadBookQuote{};
    SpreadCloseMark msgSpreadCloseMark{};
    SpreadMarketSummary msgSpreadMarketSummary{};
    SpreadOpenMark msgSpreadOpenMark{};
    SpreadPrint msgSpreadPrint{};
    AuctionNotice msgAuctionNotice{};
    AuctionNoticeBX msgAuctionNoticeBX{};
    AuctionNoticeRC msgAuctionNoticeRC{};
    AuctionNoticeSN msgAuctionNoticeSN{};
    AuctionPrint msgAuctionPrint{};
    AuctionPrintBX msgAuctionPrintBX{};
    AuctionPrintRC msgAuctionPrintRC{};
    AuctionPrintSN msgAuctionPrintSN{};
    AuctionState msgAuctionState{};
    AutoResponderBX msgAutoResponderBX{};
    AutoResponderRC msgAutoResponderRC{};
    AutoResponderSN msgAutoResponderSN{};
    AutoResponderVegaDir msgAutoResponderVegaDir{};
    NoticeCancel msgNoticeCancel{};
    NoticeExecReport msgNoticeExecReport{};
    NoticeResponse msgNoticeResponse{};
    ResponderMarkupBX msgResponderMarkupBX{};
    ResponderMarkupRC msgResponderMarkupRC{};
    ResponderMarkupSN msgResponderMarkupSN{};
    ResponderMarkupVegaDir msgResponderMarkupVegaDir{};
    UserAuctionFilter msgUserAuctionFilter{};
    UserAuctionTickerFilter msgUserAuctionTickerFilter{};
    IndustryDefinition msgIndustryDefinition{};
    LiveBasisCurve msgLiveBasisCurve{};
    LiveExpiryAtm msgLiveExpiryAtm{};
    LiveExpirySurface msgLiveExpirySurface{};
    LiveIVarSwapFixedTerm msgLiveIVarSwapFixedTerm{};
    LiveSurfaceAtm msgLiveSurfaceAtm{};
    LiveSurfacePerf msgLiveSurfacePerf{};
    OptionLookback msgOptionLookback{};
    OptionOpenVega msgOptionOpenVega{};
    OptionPrintSetSummary msgOptionPrintSetSummary{};
    SpanRiskCalculator msgSpanRiskCalculator{};
    StockBorrowRate msgStockBorrowRate{};
    StockDetail msgStockDetail{};
    SyntheticExpiryCloseMark msgSyntheticExpiryCloseMark{};
    SyntheticExpiryOpenMark msgSyntheticExpiryOpenMark{};
    VolTimeCalculator msgVolTimeCalculator{};
    StockPrintProbability msgStockPrintProbability{};
    StockQuoteProbability msgStockQuoteProbability{};
    WshFutureQuarters msgWshFutureQuarters{};



    public:

    std::atomic<uint64_t> mHeartBeatCounter = 0;

    // Callback for SubscribeAck messages
    struct SubscribeData {
        std::string mSubscribeString;
        spiderrock::protobuf::api::SubscribeMsgResult mResult = spiderrock::protobuf::api::SubscribeMsgResult::SUBSCRIBEMSGRESULT_UNSPECIFIED;
    };
    std::function<void(std::unique_ptr<SubscribeData>)> mSubscribeAckCallback = nullptr;

    // Callback for stream messages
    struct StreamData {
         spiderrock::protobuf::api::MLinkStreamState mResult =  spiderrock::protobuf::api::MLinkStreamState::MLINKSTREAMSTATE_UNSPECIFIED;
    };
    std::function<void(std::unique_ptr<StreamData>)> mMLinkStreamCheckPtCallback = nullptr;

    enum class AuctionType {
        unknown,
        open,
        close
    };
    struct CrossTradeInfo {
        AuctionType mAucionType =  AuctionType::unknown;
        std::string mTicker;
        uint64_t mTimeStamp = 0;
    };
    std::function<void(std::unique_ptr<CrossTradeInfo>)> mCrossTradeCallback = nullptr;

    uint64_t mNumberPrintMessages = 0;

    int process_buffer(const char* buf, int len) {
        int processed = 0;
        const char* msg = buf;
        while ((msg - buf) + 14 <= len) {
            if (msg[0] == '\r' && msg[1] == '\n' && msg[2] == 'P') {
                // Extract messageTypeNumber and messageLength
                int messageTypeNumber = 0;
                for (int i = 3; i < 8; ++i) {
                    if (msg[i] >= '0' && msg[i] <= '9') {
                        messageTypeNumber = messageTypeNumber * 10 + msg[i] - '0';
                    }
                    else {
                        std::cout << "Invalid message format (1)" << std::endl;
                        // Handle invalid message format
                         break;
                    }
                }
                int messageLength = 0;
                for (int i = 8; i < 14; ++i) {
                    if (msg[i] >= '0' && msg[i] <= '9') {
                        messageLength = messageLength * 10 + msg[i] - '0';
                    }
                    else {
                        std::cout << "Invalid message format (2)" << std::endl;
                        // Handle invalid message format
                        break;
                    }
                }
                // Ensure that the message is long enough
                if ((msg - buf) + 14 + messageLength <= len) {
                    // Dispatch the message with messageTypeNumber and messageLength
                    dispatch_message(messageTypeNumber, msg + 14, messageLength);
                    msg += 14 + messageLength;
                    processed += 14 + messageLength;
                }
                else {
                    std::cout << "Invalid message format (3)" << std::endl;
                    // Message is incomplete, break out of the loop
                    break;
                }
            }
            else {
                std::cout << "Invalid message format (4)" << std::endl;
                 // Invalid message format, break out of the loop
                break;
            }
        } // end of while
        return processed;
    }

    void dispatch_message(int message_number, const char *buf, int len) {
        switch (message_number) {
            case 1810: {  // AccountRouteConfig
			    msgAccountRouteConfig.Clear();
                msgAccountRouteConfig.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1815: {  // AltSymbolMap
			    msgAltSymbolMap.Clear();
                msgAltSymbolMap.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1630: {  // AssetAccountControl
			    msgAssetAccountControl.Clear();
                msgAssetAccountControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1725: {  // AvailableStockLocates
			    msgAvailableStockLocates.Clear();
                msgAvailableStockLocates.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1635: {  // BookControl
			    msgBookControl.Clear();
                msgBookControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1830: {  // ClientAccntStrategyMap
			    msgClientAccntStrategyMap.Clear();
                msgClientAccntStrategyMap.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1835: {  // ClientAccountConfig
			    msgClientAccountConfig.Clear();
                msgClientAccountConfig.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1731: {  // ClientStockLocate
			    msgClientStockLocate.Clear();
                msgClientStockLocate.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1640: {  // CustomControl
			    msgCustomControl.Clear();
                msgCustomControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1645: {  // ExpirationControl
			    msgExpirationControl.Clear();
                msgExpirationControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1650: {  // FutureControl
			    msgFutureControl.Clear();
                msgFutureControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4540: {  // GlobalRiskControl
			    msgGlobalRiskControl.Clear();
                msgGlobalRiskControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1655: {  // IndustryControl
			    msgIndustryControl.Clear();
                msgIndustryControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4675: {  // MarRiskComposite
			    msgMarRiskComposite.Clear();
                msgMarRiskComposite.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4550: {  // MarRiskControl
			    msgMarRiskControl.Clear();
                msgMarRiskControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4551: {  // MarRiskControlTkOverride
			    msgMarRiskControlTkOverride.Clear();
                msgMarRiskControlTkOverride.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4670: {  // MarRiskCounter
			    msgMarRiskCounter.Clear();
                msgMarRiskCounter.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1660: {  // RiskClassControl
			    msgRiskClassControl.Clear();
                msgRiskClassControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1665: {  // SectorControl
			    msgSectorControl.Clear();
                msgSectorControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4560: {  // SpdrRiskControl
			    msgSpdrRiskControl.Clear();
                msgSpdrRiskControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4660: {  // SpdrRiskCounter
			    msgSpdrRiskCounter.Clear();
                msgSpdrRiskCounter.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1735: {  // StockLocateRequest
			    msgStockLocateRequest.Clear();
                msgStockLocateRequest.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1740: {  // StockLocateResponse
			    msgStockLocateResponse.Clear();
                msgStockLocateResponse.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1745: {  // StockPoolBorrowRate
			    msgStockPoolBorrowRate.Clear();
                msgStockPoolBorrowRate.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3065: {  // StockThreshold
			    msgStockThreshold.Clear();
                msgStockThreshold.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1670: {  // SymbolControl
			    msgSymbolControl.Clear();
                msgSymbolControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3630: {  // UserDividendOverride
			    msgUserDividendOverride.Clear();
                msgUserDividendOverride.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3635: {  // UserRateOverride
			    msgUserRateOverride.Clear();
                msgUserRateOverride.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2675: {  // IndexQuote
			    msgIndexQuote.Clear();
                msgIndexQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4485: {  // MarketHoursConfig
			    msgMarketHoursConfig.Clear();
                msgMarketHoursConfig.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4450: {  // NMSCircuitBreaker
			    msgNMSCircuitBreaker.Clear();
                msgNMSCircuitBreaker.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2750: {  // OpraPrintType
			    msgOpraPrintType.Clear();
                msgOpraPrintType.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2760: {  // OptionEOP
			    msgOptionEOP.Clear();
                msgOptionEOP.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2790: {  // OptionOpenAuction
			    msgOptionOpenAuction.Clear();
                msgOptionOpenAuction.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2795: {  // OptionOpenAuctionSummary
			    msgOptionOpenAuctionSummary.Clear();
                msgOptionOpenAuctionSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2805: {  // OptionPrint2
			    msgOptionPrint2.Clear();
                msgOptionPrint2.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2825: {  // OptionPrintSummary
			    msgOptionPrintSummary.Clear();
                msgOptionPrintSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3150: {  // OptionSettlementMark
			    msgOptionSettlementMark.Clear();
                msgOptionSettlementMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4460: {  // ProductPriceBand
			    msgProductPriceBand.Clear();
                msgProductPriceBand.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4465: {  // ProductTradingStatus
			    msgProductTradingStatus.Clear();
                msgProductTradingStatus.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4470: {  // ProductTradingStatusV2
			    msgProductTradingStatusV2.Clear();
                msgProductTradingStatusV2.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 6225: {  // RFQQuoteBroadcast
			    msgRFQQuoteBroadcast.Clear();
                msgRFQQuoteBroadcast.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2830: {  // SOQConstituentSymbolMap
			    msgSOQConstituentSymbolMap.Clear();
                msgSOQConstituentSymbolMap.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2835: {  // SOQStrikeRangeUpdate
			    msgSOQStrikeRangeUpdate.Clear();
                msgSOQStrikeRangeUpdate.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2995: {  // StockAuctionSummary
			    msgStockAuctionSummary.Clear();
                msgStockAuctionSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3015: {  // StockExchImbalance
			    msgStockExchImbalance.Clear();
                msgStockExchImbalance.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3035: {  // StockImbalance
			    msgStockImbalance.Clear();
                msgStockImbalance.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4475: {  // StockRegSHOStatus
			    msgStockRegSHOStatus.Clear();
                msgStockRegSHOStatus.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2700: {  // SyntheticExpiryQuote
			    msgSyntheticExpiryQuote.Clear();
                msgSyntheticExpiryQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2695: {  // SyntheticFutureQuote
			    msgSyntheticFutureQuote.Clear();
                msgSyntheticFutureQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4745: {  // AccountRiskRecordV5
			    msgAccountRiskRecordV5.Clear();
                msgAccountRiskRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1945: {  // ClientBeta
			    msgClientBeta.Clear();
                msgClientBeta.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4750: {  // CurrencyPositionRecordV5
			    msgCurrencyPositionRecordV5.Clear();
                msgCurrencyPositionRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4755: {  // CurrencyTransaction
			    msgCurrencyTransaction.Clear();
                msgCurrencyTransaction.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4760: {  // EquityCorpActionRecordV5
			    msgEquityCorpActionRecordV5.Clear();
                msgEquityCorpActionRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4765: {  // ExpirationRiskRecordV5
			    msgExpirationRiskRecordV5.Clear();
                msgExpirationRiskRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4775: {  // FuturePositionRecordV5
			    msgFuturePositionRecordV5.Clear();
                msgFuturePositionRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4780: {  // FutureRiskDetailV5
			    msgFutureRiskDetailV5.Clear();
                msgFutureRiskDetailV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4785: {  // FutureRiskSummaryV5
			    msgFutureRiskSummaryV5.Clear();
                msgFutureRiskSummaryV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4790: {  // IndustryRiskRecordV5
			    msgIndustryRiskRecordV5.Clear();
                msgIndustryRiskRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4795: {  // OptionCorpActionRecordV5
			    msgOptionCorpActionRecordV5.Clear();
                msgOptionCorpActionRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4800: {  // OptionExAsRecordV5
			    msgOptionExAsRecordV5.Clear();
                msgOptionExAsRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4805: {  // OptionPositionRecordV5
			    msgOptionPositionRecordV5.Clear();
                msgOptionPositionRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4810: {  // ProductRiskDetailV5
			    msgProductRiskDetailV5.Clear();
                msgProductRiskDetailV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4815: {  // ProductRiskSummaryV5
			    msgProductRiskSummaryV5.Clear();
                msgProductRiskSummaryV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4820: {  // RiskAggGroupStateV5
			    msgRiskAggGroupStateV5.Clear();
                msgRiskAggGroupStateV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4825: {  // RiskCubeDetailV5
			    msgRiskCubeDetailV5.Clear();
                msgRiskCubeDetailV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4830: {  // SodCashRecordV5
			    msgSodCashRecordV5.Clear();
                msgSodCashRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4835: {  // SodClearingRecordV5
			    msgSodClearingRecordV5.Clear();
                msgSodClearingRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4850: {  // StockPositionRecordV5
			    msgStockPositionRecordV5.Clear();
                msgStockPositionRecordV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4855: {  // SymbolMarginSummaryV5
			    msgSymbolMarginSummaryV5.Clear();
                msgSymbolMarginSummaryV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4860: {  // SymbolRiskDetailV5
			    msgSymbolRiskDetailV5.Clear();
                msgSymbolRiskDetailV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4865: {  // SymbolRiskSummaryV5
			    msgSymbolRiskSummaryV5.Clear();
                msgSymbolRiskSummaryV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4870: {  // TradeCubeDetailV5
			    msgTradeCubeDetailV5.Clear();
                msgTradeCubeDetailV5.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 5055: {  // OptionTheoVol
			    msgOptionTheoVol.Clear();
                msgOptionTheoVol.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1950: {  // SpdrOptTheoRecord
			    msgSpdrOptTheoRecord.Clear();
                msgSpdrOptTheoRecord.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1955: {  // SpdrTheoExp2PtCurve
			    msgSpdrTheoExp2PtCurve.Clear();
                msgSpdrTheoExp2PtCurve.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1960: {  // SpdrTheoExpSurface
			    msgSpdrTheoExpSurface.Clear();
                msgSpdrTheoExpSurface.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1105: {  // TheoSurfacePerf
			    msgTheoSurfacePerf.Clear();
                msgTheoSurfacePerf.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 5290: {  // AutoHedgeSymbol
			    msgAutoHedgeSymbol.Clear();
                msgAutoHedgeSymbol.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2270: {  // ExternAggGroupReport
			    msgExternAggGroupReport.Clear();
                msgExternAggGroupReport.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4655: {  // RiskGroupCounter
			    msgRiskGroupCounter.Clear();
                msgRiskGroupCounter.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3985: {  // SpdrAccntCancel
			    msgSpdrAccntCancel.Clear();
                msgSpdrAccntCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3695: {  // SpdrAllocationNotice
			    msgSpdrAllocationNotice.Clear();
                msgSpdrAllocationNotice.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3700: {  // SpdrAllocationNoticeStatus
			    msgSpdrAllocationNoticeStatus.Clear();
                msgSpdrAllocationNoticeStatus.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 5295: {  // SpdrAutoHedgeControl
			    msgSpdrAutoHedgeControl.Clear();
                msgSpdrAutoHedgeControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 5300: {  // SpdrAutoHedgeState
			    msgSpdrAutoHedgeState.Clear();
                msgSpdrAutoHedgeState.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3705: {  // SpdrAvailExecAllocation
			    msgSpdrAvailExecAllocation.Clear();
                msgSpdrAvailExecAllocation.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1450: {  // SpdrAwayExecution
			    msgSpdrAwayExecution.Clear();
                msgSpdrAwayExecution.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3990: {  // SpdrBrokerCancel
			    msgSpdrBrokerCancel.Clear();
                msgSpdrBrokerCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3920: {  // SpdrClientFirmRiskMgmt
			    msgSpdrClientFirmRiskMgmt.Clear();
                msgSpdrClientFirmRiskMgmt.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1460: {  // SpdrDropExecution
			    msgSpdrDropExecution.Clear();
                msgSpdrDropExecution.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1465: {  // SpdrDropExecutionAck
			    msgSpdrDropExecutionAck.Clear();
                msgSpdrDropExecutionAck.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1470: {  // SpdrExchRiskDrop
			    msgSpdrExchRiskDrop.Clear();
                msgSpdrExchRiskDrop.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3925: {  // SpdrExchRiskMgmt
			    msgSpdrExchRiskMgmt.Clear();
                msgSpdrExchRiskMgmt.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3835: {  // SpdrExchRiskReset
			    msgSpdrExchRiskReset.Clear();
                msgSpdrExchRiskReset.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3710: {  // SpdrExecutionAllocation
			    msgSpdrExecutionAllocation.Clear();
                msgSpdrExecutionAllocation.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3715: {  // SpdrExecutionAllocationStatus
			    msgSpdrExecutionAllocationStatus.Clear();
                msgSpdrExecutionAllocationStatus.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4025: {  // SpdrMLegBrkrEvent
			    msgSpdrMLegBrkrEvent.Clear();
                msgSpdrMLegBrkrEvent.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4030: {  // SpdrMLegBrkrState
			    msgSpdrMLegBrkrState.Clear();
                msgSpdrMLegBrkrState.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3720: {  // SpdrOmniOrder
			    msgSpdrOmniOrder.Clear();
                msgSpdrOmniOrder.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3725: {  // SpdrParentAllocation
			    msgSpdrParentAllocation.Clear();
                msgSpdrParentAllocation.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3730: {  // SpdrParentAllocationStatus
			    msgSpdrParentAllocationStatus.Clear();
                msgSpdrParentAllocationStatus.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4065: {  // SpdrParentBrkrEvent
			    msgSpdrParentBrkrEvent.Clear();
                msgSpdrParentBrkrEvent.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4070: {  // SpdrParentBrkrState
			    msgSpdrParentBrkrState.Clear();
                msgSpdrParentBrkrState.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4075: {  // SpdrParentBrokerSummary
			    msgSpdrParentBrokerSummary.Clear();
                msgSpdrParentBrokerSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4080: {  // SpdrParentCancel
			    msgSpdrParentCancel.Clear();
                msgSpdrParentCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4085: {  // SpdrParentExecution
			    msgSpdrParentExecution.Clear();
                msgSpdrParentExecution.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4090: {  // SpdrParentLimit
			    msgSpdrParentLimit.Clear();
                msgSpdrParentLimit.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4095: {  // SpdrParentOrder
			    msgSpdrParentOrder.Clear();
                msgSpdrParentOrder.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4100: {  // SpdrParentReport
			    msgSpdrParentReport.Clear();
                msgSpdrParentReport.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4195: {  // SpdrParentReviewRequest
			    msgSpdrParentReviewRequest.Clear();
                msgSpdrParentReviewRequest.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4200: {  // SpdrParentReviewResponse
			    msgSpdrParentReviewResponse.Clear();
                msgSpdrParentReviewResponse.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4105: {  // SpdrReleaseWaitTrigger
			    msgSpdrReleaseWaitTrigger.Clear();
                msgSpdrReleaseWaitTrigger.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2325: {  // SpdrRiskExecution
			    msgSpdrRiskExecution.Clear();
                msgSpdrRiskExecution.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1467: {  // SpdrRiskGroupCancel
			    msgSpdrRiskGroupCancel.Clear();
                msgSpdrRiskGroupCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4570: {  // SpdrRiskGroupControl
			    msgSpdrRiskGroupControl.Clear();
                msgSpdrRiskGroupControl.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4110: {  // SpdrRouteCancel
			    msgSpdrRouteCancel.Clear();
                msgSpdrRouteCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4115: {  // SpdrSecKeyCancel
			    msgSpdrSecKeyCancel.Clear();
                msgSpdrSecKeyCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4120: {  // SpdrSetActiveSize
			    msgSpdrSetActiveSize.Clear();
                msgSpdrSetActiveSize.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4135: {  // SpdrStripeTrigger
			    msgSpdrStripeTrigger.Clear();
                msgSpdrStripeTrigger.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2330: {  // SpdrSweepDetail
			    msgSpdrSweepDetail.Clear();
                msgSpdrSweepDetail.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2335: {  // SpdrSweepExchDetail
			    msgSpdrSweepExchDetail.Clear();
                msgSpdrSweepExchDetail.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4140: {  // SpdrUserCancel
			    msgSpdrUserCancel.Clear();
                msgSpdrUserCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3480: {  // ToolCompositeExecution
			    msgToolCompositeExecution.Clear();
                msgToolCompositeExecution.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3245: {  // StockBetaExt
			    msgStockBetaExt.Clear();
                msgStockBetaExt.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3620: {  // StockEarningsCalendar
			    msgStockEarningsCalendar.Clear();
                msgStockEarningsCalendar.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3055: {  // StockPrintMarkup
			    msgStockPrintMarkup.Clear();
                msgStockPrintMarkup.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3060: {  // StockPrintSet
			    msgStockPrintSet.Clear();
                msgStockPrintSet.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3255: {  // TickerAnalytics
			    msgTickerAnalytics.Clear();
                msgTickerAnalytics.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3640: {  // UserSDivOverride
			    msgUserSDivOverride.Clear();
                msgUserSDivOverride.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3020: {  // StockExchImbalanceV2
			    msgStockExchImbalanceV2.Clear();
                msgStockExchImbalanceV2.ParseFromArray(buf, len);
                //std::cout << "Raw ---------- Start " << std::endl;
                //std::ostream *o = &std::cout;
                //*o << msgStockExchImbalanceV2;
                //std::cout << std::endl << "Raw ---------- End " << std::endl;
                //std::cout << __LINE__  << std::endl;
                break;
            }
            case 3165: {  // StockCloseMark
			    msgStockCloseMark.Clear();
                msgStockCloseMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3170: {  // StockOpenMark
			    msgStockOpenMark.Clear();
                msgStockOpenMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3000: {  // StockBookQuote
			    msgStockBookQuote.Clear();
                msgStockBookQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3045: {  // StockPrint
			    msgStockPrint.Clear();
                msgStockPrint.ParseFromArray(buf, len);
                //std::cout << __LINE__  << std::endl; //Active
                //std::cout << "Raw ---------- Start " << std::endl;
                //std::ostream *o = &std::cout;
                //*o << msgStockPrint;
                //std::cout << std::endl << "Raw ---------- End " << std::endl;


                mNumberPrintMessages++;

                //Continue only if the message is for NYSE
                spiderrock::protobuf::api::StkExch lExchange = msgStockPrint.get_prt_exch();
                if (lExchange != spiderrock::protobuf::api::StkExch::STKEXCH_NYSE) {
                    break; // Skip non-NYSE exchanges
                }

                //Continue only if the message is open or close
                uint32_t lPrintCondition = msgStockPrint.get_prt_cond2();
                lPrintCondition = lPrintCondition & 0xff;
                if (lPrintCondition != 79 && //open
                    lPrintCondition != 54) { //close
                    break; // Skip non-open/close prints
                }

                auto lData = std::make_unique<CrossTradeInfo>();

                const TickerKey lSpiderRockTicker = msgStockPrint.get_pkey().get_ticker();
                lData->mTicker = lSpiderRockTicker.get_ticker();

                if (lPrintCondition == 79) { //open
                    lData->mAucionType = AuctionType::open;
                } else if (lPrintCondition == 54) { //close
                    lData->mAucionType = AuctionType::close;
                } else {
                    lData->mAucionType = AuctionType::unknown;
                }
                lData->mTimeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(msgStockPrint.get_timestamp().time_since_epoch()).count();

                if (mCrossTradeCallback) {
                    mCrossTradeCallback(std::move(lData));
                } else {
                    throw std::runtime_error("CrossTrade callback not defined");
                }

                break;
            }
            case 3040: {  // StockMarketSummary
			    msgStockMarketSummary.Clear();
                msgStockMarketSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1175: {  // StockMinuteBar
			    msgStockMinuteBar.Clear();
                msgStockMinuteBar.ParseFromArray(buf, len);
                //std::ostream *o = &std::cout;
                //*o << msgStockMinuteBar << std::endl;
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4400: {  // RegionalUnderlierComposite
			    msgRegionalUnderlierComposite.Clear();
                msgRegionalUnderlierComposite.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4375: {  // TickerDefinition
			    msgTickerDefinition.Clear();
                msgTickerDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4380: {  // TickerDefinitionExt
			    msgTickerDefinitionExt.Clear();
                msgTickerDefinitionExt.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2605: {  // FuturePrintMarkup
			    msgFuturePrintMarkup.Clear();
                msgFuturePrintMarkup.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2610: {  // FuturePrintSet
			    msgFuturePrintSet.Clear();
                msgFuturePrintSet.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3120: {  // FutureCloseMark
			    msgFutureCloseMark.Clear();
                msgFutureCloseMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3125: {  // FutureOpenMark
			    msgFutureOpenMark.Clear();
                msgFutureOpenMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3130: {  // FutureSettlementMark
			    msgFutureSettlementMark.Clear();
                msgFutureSettlementMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2580: {  // FutureBookQuote
			    msgFutureBookQuote.Clear();
                msgFutureBookQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2595: {  // FuturePrint
			    msgFuturePrint.Clear();
                msgFuturePrint.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4255: {  // FuturePrintProbability
			    msgFuturePrintProbability.Clear();
                msgFuturePrintProbability.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4260: {  // FutureQuoteProbability
			    msgFutureQuoteProbability.Clear();
                msgFutureQuoteProbability.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2590: {  // FutureMarketSummary
			    msgFutureMarketSummary.Clear();
                msgFutureMarketSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1160: {  // FutureMinuteBar
			    msgFutureMinuteBar.Clear();
                msgFutureMinuteBar.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4335: {  // CCodeDefinition
			    msgCCodeDefinition.Clear();
                msgCCodeDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4360: {  // ProductDefinitionV2
			    msgProductDefinitionV2.Clear();
                msgProductDefinitionV2.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2540: {  // CurrencyConversion
			    msgCurrencyConversion.Clear();
                msgCurrencyConversion.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3590: {  // GlobalDividends
			    msgGlobalDividends.Clear();
                msgGlobalDividends.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3595: {  // GlobalRates
			    msgGlobalRates.Clear();
                msgGlobalRates.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3456: {  // AggregateCount
			    msgAggregateCount.Clear();
                msgAggregateCount.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3450: {  // AggregateNumeric
			    msgAggregateNumeric.Clear();
                msgAggregateNumeric.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3455: {  // AggregateString
			    msgAggregateString.Clear();
                msgAggregateString.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3460: {  // BucketRange
			    msgBucketRange.Clear();
                msgBucketRange.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3325: {  // FieldDesc
			    msgFieldDesc.Clear();
                msgFieldDesc.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3360: {  // MLinkCount
			    msgMLinkCount.Clear();
                msgMLinkCount.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3415: {  // MsgDesc
			    msgMsgDesc.Clear();
                msgMsgDesc.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3420: {  // MsgExpiryKey
			    msgMsgExpiryKey.Clear();
                msgMsgExpiryKey.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3430: {  // MsgOptionKey
			    msgMsgOptionKey.Clear();
                msgMsgOptionKey.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3435: {  // MsgTickerKey
			    msgMsgTickerKey.Clear();
                msgMsgTickerKey.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3440: {  // PostAck
			    msgPostAck.Clear();
                msgPostAck.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3445: {  // QueryResult
			    msgQueryResult.Clear();
                msgQueryResult.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3476: {  // UserApiKey
			    msgUserApiKey.Clear();
                msgUserApiKey.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3470: {  // UserMetaData
			    msgUserMetaData.Clear();
                msgUserMetaData.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3345: {  // MLinkAdmin
			    msgMLinkAdmin.Clear();
                msgMLinkAdmin.ParseFromArray(buf, len);
                spiderrock::protobuf::api::HttpSessionState lState = msgMLinkAdmin.get_state();
                std::cout << "MLink Admin"  << std::endl;
                std::cout << " State: " << std::to_string((uint8_t)lState) << std::endl;
                std::cout << " Detail: " << msgMLinkAdmin.get_detail() << std::endl;
                break;
            }
            case 3365: {  // MLinkDataAck
			    msgMLinkDataAck.Clear();
                msgMLinkDataAck.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3368: {  // MLinkHeartbeat
			    msgMLinkHeartbeat.Clear();
                msgMLinkHeartbeat.ParseFromArray(buf, len);
                mHeartBeatCounter++;
                break;
            }
            case 3370: {  // MLinkLogon
			    msgMLinkLogon.Clear();
                msgMLinkLogon.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3410: {  // MLinkSignalReady
			    msgMLinkSignalReady.Clear();
                msgMLinkSignalReady.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3380: {  // MLinkStream
			    msgMLinkStream.Clear();
                msgMLinkStream.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3381: {  // MLinkStreamAck
			    msgMLinkStreamAck.Clear();
                msgMLinkStreamAck.ParseFromArray(buf, len);
                spiderrock::protobuf::api::AckResult lResult = msgMLinkStreamAck.get_result();
                std::cout << "MLink Stream Ack: " << msgMLinkStreamAck.get_msg_name() << " Result: " << std::to_string((uint8_t)lResult) << std::endl;
                break;
            }
            case 3382: {  // MLinkStreamCheckPt
			    msgMLinkStreamCheckPt.Clear();
                msgMLinkStreamCheckPt.ParseFromArray(buf, len);

                //std::ostream *o = &std::cout;
                //*o << msgMLinkStreamCheckPt;
                //std::cout << __LINE__  << std::endl; //Active

                if (!mMLinkStreamCheckPtCallback) {
                    throw std::runtime_error(" MLinkStreamCheckPt Callback callback not set");
                }

                auto lStreamData = std::make_unique<StreamData>();
                lStreamData->mResult = msgMLinkStreamCheckPt.get_state();
                mMLinkStreamCheckPtCallback(std::move(lStreamData));
                break;
            }
            case 3386: {  // MLinkSubscribe
			    msgMLinkSubscribe.Clear();
                msgMLinkSubscribe.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3387: {  // MLinkSubscribeAck
			    msgMLinkSubscribeAck.Clear();
                msgMLinkSubscribeAck.ParseFromArray(buf, len);
                //std::cout << "msgMLinkSubscribeAck: " << __LINE__  << std::endl;

                auto lSubscribeData = std::make_unique<SubscribeData>();
                auto lSubscribeResponseVector = msgMLinkSubscribeAck.get_subscribe_list();
                if (lSubscribeResponseVector.size() != 1) {
                    throw std::runtime_error("MLinkSubscribeAck should contain exactly one subscribe response");
                }
                const auto& msgMLinkSubscribeResponse = lSubscribeResponseVector[0];
                lSubscribeData->mSubscribeString = msgMLinkSubscribeResponse.get_msg_pkey();
                lSubscribeData->mResult = msgMLinkSubscribeResponse.get_result();
                if (lSubscribeData->mResult != spiderrock::protobuf::api::SubscribeMsgResult::SUBSCRIBEMSGRESULT_OK) {
                    std::ostream *o = &std::cout;
                    *o << msgMLinkSubscribeAck << std::endl;
                }

                if (!mSubscribeAckCallback) {
                    throw std::runtime_error("Subscribe callback not set");
                }
                mSubscribeAckCallback(std::move(lSubscribeData));

                break;
            }
            case 3388: {  // MLinkSubscribeCheckPt
			    msgMLinkSubscribeCheckPt.Clear();
                msgMLinkSubscribeCheckPt.ParseFromArray(buf, len);
                //std::cout << __LINE__  << std::endl;
                //std::ostream *o = &std::cout;
                //*o << msgMLinkSubscribeCheckPt << std::endl;
                break;
            }
            case 7800: {  // NationsIndexPrice
			    msgNationsIndexPrice.Clear();
                msgNationsIndexPrice.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1015: {  // LiveImpliedQuote
			    msgLiveImpliedQuote.Clear();
                msgLiveImpliedQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1020: {  // LiveImpliedQuoteAdj
			    msgLiveImpliedQuoteAdj.Clear();
                msgLiveImpliedQuoteAdj.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1017: {  // LiveImpliedQuoteDisp
			    msgLiveImpliedQuoteDisp.Clear();
                msgLiveImpliedQuoteDisp.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1125: {  // LiveRevConQuote
			    msgLiveRevConQuote.Clear();
                msgLiveRevConQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2815: {  // OptionPrintSet
			    msgOptionPrintSet.Clear();
                msgOptionPrintSet.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1095: {  // OptionRiskFactor
			    msgOptionRiskFactor.Clear();
                msgOptionRiskFactor.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3240: {  // StockBeta
			    msgStockBeta.Clear();
                msgStockBeta.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2525: {  // SpdrAuctionState
			    msgSpdrAuctionState.Clear();
                msgSpdrAuctionState.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4355: {  // OptExpiryDefinition
			    msgOptExpiryDefinition.Clear();
                msgOptExpiryDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4410: {  // RegionalInstrumentId
			    msgRegionalInstrumentId.Clear();
                msgRegionalInstrumentId.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4405: {  // RegionalOptionComposite
			    msgRegionalOptionComposite.Clear();
                msgRegionalOptionComposite.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4365: {  // RootDefinition
			    msgRootDefinition.Clear();
                msgRootDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3140: {  // OptionCloseMark
			    msgOptionCloseMark.Clear();
                msgOptionCloseMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3230: {  // OptionOpenInterest
			    msgOptionOpenInterest.Clear();
                msgOptionOpenInterest.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3145: {  // OptionOpenMark
			    msgOptionOpenMark.Clear();
                msgOptionOpenMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2845: {  // OptionFlexEvent
			    msgOptionFlexEvent.Clear();
                msgOptionFlexEvent.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2785: {  // OptionNbboQuote
			    msgOptionNbboQuote.Clear();
                msgOptionNbboQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2800: {  // OptionPrint
			    msgOptionPrint.Clear();
                msgOptionPrint.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4265: {  // OptionPrintProbability
			    msgOptionPrintProbability.Clear();
                msgOptionPrintProbability.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4270: {  // OptionQuoteProbability
			    msgOptionQuoteProbability.Clear();
                msgOptionQuoteProbability.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2780: {  // OptionMarketSummary
			    msgOptionMarketSummary.Clear();
                msgOptionMarketSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3225: {  // HistoricalVolatilities
			    msgHistoricalVolatilities.Clear();
                msgHistoricalVolatilities.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1010: {  // LiveAtmVol
			    msgLiveAtmVol.Clear();
                msgLiveAtmVol.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1035: {  // LiveSurfaceCurve
			    msgLiveSurfaceCurve.Clear();
                msgLiveSurfaceCurve.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1040: {  // LiveSurfaceFixedGrid
			    msgLiveSurfaceFixedGrid.Clear();
                msgLiveSurfaceFixedGrid.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1045: {  // LiveSurfaceFixedTerm
			    msgLiveSurfaceFixedTerm.Clear();
                msgLiveSurfaceFixedTerm.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 6820: {  // OptionAtmMinuteBarData
			    msgOptionAtmMinuteBarData.Clear();
                msgOptionAtmMinuteBarData.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3485: {  // GetOptionBasket
			    msgGetOptionBasket.Clear();
                msgGetOptionBasket.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3335: {  // GetOptionPrice
			    msgGetOptionPrice.Clear();
                msgGetOptionPrice.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3340: {  // GetOptionVolatility
			    msgGetOptionVolatility.Clear();
                msgGetOptionVolatility.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3487: {  // OptionItemCalc
			    msgOptionItemCalc.Clear();
                msgOptionItemCalc.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3486: {  // OptionItemDef
			    msgOptionItemDef.Clear();
                msgOptionItemDef.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4390: {  // SpreadDefinition
			    msgSpreadDefinition.Clear();
                msgSpreadDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4395: {  // SpreadExchDefinition
			    msgSpreadExchDefinition.Clear();
                msgSpreadExchDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2915: {  // SpreadExchOrder
			    msgSpreadExchOrder.Clear();
                msgSpreadExchOrder.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2895: {  // SpreadBookMarkup
			    msgSpreadBookMarkup.Clear();
                msgSpreadBookMarkup.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2900: {  // SpreadBookQuote
			    msgSpreadBookQuote.Clear();
                msgSpreadBookQuote.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3155: {  // SpreadCloseMark
			    msgSpreadCloseMark.Clear();
                msgSpreadCloseMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2925: {  // SpreadMarketSummary
			    msgSpreadMarketSummary.Clear();
                msgSpreadMarketSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3160: {  // SpreadOpenMark
			    msgSpreadOpenMark.Clear();
                msgSpreadOpenMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2930: {  // SpreadPrint
			    msgSpreadPrint.Clear();
                msgSpreadPrint.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2465: {  // AuctionNotice
			    msgAuctionNotice.Clear();
                msgAuctionNotice.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2468: {  // AuctionNoticeBX
			    msgAuctionNoticeBX.Clear();
                msgAuctionNoticeBX.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2466: {  // AuctionNoticeRC
			    msgAuctionNoticeRC.Clear();
                msgAuctionNoticeRC.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2467: {  // AuctionNoticeSN
			    msgAuctionNoticeSN.Clear();
                msgAuctionNoticeSN.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2485: {  // AuctionPrint
			    msgAuctionPrint.Clear();
                msgAuctionPrint.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2488: {  // AuctionPrintBX
			    msgAuctionPrintBX.Clear();
                msgAuctionPrintBX.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2486: {  // AuctionPrintRC
			    msgAuctionPrintRC.Clear();
                msgAuctionPrintRC.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2487: {  // AuctionPrintSN
			    msgAuctionPrintSN.Clear();
                msgAuctionPrintSN.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2464: {  // AuctionState
			    msgAuctionState.Clear();
                msgAuctionState.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2498: {  // AutoResponderBX
			    msgAutoResponderBX.Clear();
                msgAutoResponderBX.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2496: {  // AutoResponderRC
			    msgAutoResponderRC.Clear();
                msgAutoResponderRC.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2497: {  // AutoResponderSN
			    msgAutoResponderSN.Clear();
                msgAutoResponderSN.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2495: {  // AutoResponderVegaDir
			    msgAutoResponderVegaDir.Clear();
                msgAutoResponderVegaDir.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2480: {  // NoticeCancel
			    msgNoticeCancel.Clear();
                msgNoticeCancel.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2475: {  // NoticeExecReport
			    msgNoticeExecReport.Clear();
                msgNoticeExecReport.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2470: {  // NoticeResponse
			    msgNoticeResponse.Clear();
                msgNoticeResponse.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2503: {  // ResponderMarkupBX
			    msgResponderMarkupBX.Clear();
                msgResponderMarkupBX.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2501: {  // ResponderMarkupRC
			    msgResponderMarkupRC.Clear();
                msgResponderMarkupRC.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2502: {  // ResponderMarkupSN
			    msgResponderMarkupSN.Clear();
                msgResponderMarkupSN.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2500: {  // ResponderMarkupVegaDir
			    msgResponderMarkupVegaDir.Clear();
                msgResponderMarkupVegaDir.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1915: {  // UserAuctionFilter
			    msgUserAuctionFilter.Clear();
                msgUserAuctionFilter.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1916: {  // UserAuctionTickerFilter
			    msgUserAuctionTickerFilter.Clear();
                msgUserAuctionTickerFilter.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4350: {  // IndustryDefinition
			    msgIndustryDefinition.Clear();
                msgIndustryDefinition.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1131: {  // LiveBasisCurve
			    msgLiveBasisCurve.Clear();
                msgLiveBasisCurve.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1134: {  // LiveExpiryAtm
			    msgLiveExpiryAtm.Clear();
                msgLiveExpiryAtm.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1132: {  // LiveExpirySurface
			    msgLiveExpirySurface.Clear();
                msgLiveExpirySurface.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1025: {  // LiveIVarSwapFixedTerm
			    msgLiveIVarSwapFixedTerm.Clear();
                msgLiveIVarSwapFixedTerm.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1030: {  // LiveSurfaceAtm
			    msgLiveSurfaceAtm.Clear();
                msgLiveSurfaceAtm.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1055: {  // LiveSurfacePerf
			    msgLiveSurfacePerf.Clear();
                msgLiveSurfacePerf.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1090: {  // OptionLookback
			    msgOptionLookback.Clear();
                msgOptionLookback.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3235: {  // OptionOpenVega
			    msgOptionOpenVega.Clear();
                msgOptionOpenVega.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 2820: {  // OptionPrintSetSummary
			    msgOptionPrintSetSummary.Clear();
                msgOptionPrintSetSummary.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 5060: {  // SpanRiskCalculator
			    msgSpanRiskCalculator.Clear();
                msgSpanRiskCalculator.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 1730: {  // StockBorrowRate
			    msgStockBorrowRate.Clear();
                msgStockBorrowRate.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3250: {  // StockDetail
			    msgStockDetail.Clear();
                msgStockDetail.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3175: {  // SyntheticExpiryCloseMark
			    msgSyntheticExpiryCloseMark.Clear();
                msgSyntheticExpiryCloseMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 3180: {  // SyntheticExpiryOpenMark
			    msgSyntheticExpiryOpenMark.Clear();
                msgSyntheticExpiryOpenMark.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 5065: {  // VolTimeCalculator
			    msgVolTimeCalculator.Clear();
                msgVolTimeCalculator.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4275: {  // StockPrintProbability
			    msgStockPrintProbability.Clear();
                msgStockPrintProbability.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 4280: {  // StockQuoteProbability
			    msgStockQuoteProbability.Clear();
                msgStockQuoteProbability.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            case 7600: {  // WshFutureQuarters
			    msgWshFutureQuarters.Clear();
                msgWshFutureQuarters.ParseFromArray(buf, len);
                std::cout << __LINE__  << std::endl;
                break;
            }
            default:
                break;
        }
    }
};


}
}
}