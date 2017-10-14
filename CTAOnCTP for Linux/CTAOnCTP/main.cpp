#include <stdio.h>
#include "include/CTP/ThostFtdcMdApi.h"
#include "CSimpleMdSpi.h"

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "044393";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "123456";                     // 投资者密码

//104494
//jiaru753951

int main(int argc, char **argv)
{

    
	// 行情参数
	char strMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址    
    
    CThostFtdcMdApi * pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi("./");
    CThostFtdcMdSpi * pMdUserSpi = new CSimpleMdSpi(pMdUserApi);
    pMdUserApi->RegisterSpi(pMdUserSpi);
    pMdUserApi->RegisterFront(strMdFrontAddr);
    pMdUserApi->Init();
    pMdUserApi->Join();
    
    
    

	return 0;
}
