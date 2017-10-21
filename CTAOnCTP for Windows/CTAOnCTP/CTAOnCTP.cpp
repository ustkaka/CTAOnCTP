// CTAOnCTP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CTP\include\ThostFtdcMdApi.h"
#include "SimpleMdSpi.h"
#include "CTP\include\ThostFtdcTraderApi.h"
#include "SimpleTraderSpi.h"

// 链接库
#pragma comment (lib, "CTP/lib/thostmduserapi.lib")
#pragma comment (lib, "CTP/lib/thosttraderapi.lib")

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "044390";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "123456";                     // 投资者密码


// 交易参数
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb1801";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 3671;                           // 交易价格


int main()
{
	// 行情参数
	char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址

	CThostFtdcMdApi * pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CSimpleMdSpi simpleMdSpi(pMdUserApi);
	pMdUserApi->RegisterSpi(&simpleMdSpi);
	pMdUserApi->RegisterFront(gMdFrontAddr);
	pMdUserApi->Init();
	//pMdUserApi->Join();

	//交易参数
	char strTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址

	CThostFtdcTraderApi *api = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CSimpleTraderSpi simpleTraderSpi(api);
	api->RegisterSpi(&simpleTraderSpi);
	api->RegisterFront(strTradeFrontAddr);
	api->SubscribePrivateTopic(THOST_TERT_QUICK);
	api->SubscribePublicTopic(THOST_TERT_QUICK);
	api->Init();
	api->Join();

    return 0;
}

