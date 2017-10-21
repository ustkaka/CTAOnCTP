#include <stdio.h>
#include <iostream>
#include "include/CTP/ThostFtdcMdApi.h"
#include "CSimpleMdSpi.h"
#include "include/CTP/ThostFtdcTraderApi.h"
#include "CSimpleTraderSpi.h"

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "044390";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "123456";                     // 投资者密码

//104494
//jiaru753951

// 交易参数
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb1801";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 3571;                           // 交易价格

int main(int argc, char **argv)
{

    
	// 行情参数
	char strMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址    
    
    CThostFtdcMdApi * pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
    CThostFtdcMdSpi * pMdUserSpi = new CSimpleMdSpi(pMdUserApi);
    pMdUserApi->RegisterSpi(pMdUserSpi);
    pMdUserApi->RegisterFront(strMdFrontAddr);
    //pMdUserApi->Init();
    //pMdUserApi->Join();
    
    //交易参数
    char strTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址
    
    // 初始化交易线程
	std::cout << "初始化交易..." << std::endl;
	CThostFtdcTraderApi *pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
	CSimpleTraderSpi tradeSpi(pTradeUserApi);               // 创建交易回调实例
	pTradeUserApi->RegisterSpi(&tradeSpi);                      // 注册事件类
	pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
	pTradeUserApi->RegisterFront(strTradeFrontAddr);              // 设置交易前置地址
	pTradeUserApi->Init();                                      // 连接运行
    pTradeUserApi->Join();
   

	return 0;
}
