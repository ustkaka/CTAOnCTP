// CTAOnCTP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CTP\include\ThostFtdcMdApi.h"
#include "SimpleMdSpi.h"

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
TThostFtdcPriceType gLimitPrice = 3571;                           // 交易价格


int main()
{
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

