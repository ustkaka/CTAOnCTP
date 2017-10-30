// CTAOnCTP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <functional>
#include <iostream>
#include "CTP\include\ThostFtdcMdApi.h"
#include "SimpleMdSpi.h"
#include "CTP\include\ThostFtdcTraderApi.h"
#include "SimpleTraderSpi.h"
#include "SimpleStrategy.h"

// 链接库
#pragma comment (lib, "CTP/lib/thostmduserapi.lib")
#pragma comment (lib, "CTP/lib/thosttraderapi.lib")

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "";                     // 投资者密码


// 交易参数
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb1801";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 3671;                           // 交易价格

std::function<void(Tick *)> g_pfunMDEventHandlerOnTick = nullptr;




int main()
{

	// 账号密码
	std::cout << "请输入账号： ";
	scanf("%s", gInvesterID);
	std::cout << "请输入密码： ";
	scanf("%s", gInvesterPassword);

	//交易参数
	char strTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址

	CThostFtdcTraderApi *api = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CSimpleTraderSpi simpleTraderSpi(api);
	api->RegisterSpi(&simpleTraderSpi);
	api->RegisterFront(strTradeFrontAddr);
	api->SubscribePrivateTopic(THOST_TERT_QUICK);
	api->SubscribePublicTopic(THOST_TERT_QUICK);
	api->Init();
	//api->Join();

	CSimpleStrategy simpleStrategy(&simpleTraderSpi,g_pTradeInstrumentID,0.0004);

	using namespace std::placeholders;
	g_pfunMDEventHandlerOnTick = std::bind(std::mem_fn(&CSimpleStrategy::OnTick), &simpleStrategy, _1); //bind event callback function

	// 行情参数
	char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址

	CThostFtdcMdApi * pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CSimpleMdSpi simpleMdSpi(pMdUserApi);
	pMdUserApi->RegisterSpi(&simpleMdSpi);
	pMdUserApi->RegisterFront(gMdFrontAddr);
	pMdUserApi->Init();
	pMdUserApi->Join();


    return 0;
}

