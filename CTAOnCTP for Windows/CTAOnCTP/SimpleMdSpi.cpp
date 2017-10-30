#include "stdafx.h"
#include "SimpleMdSpi.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;
using Tick = CThostFtdcDepthMarketDataField;

//全局变量声明
extern TThostFtdcBrokerIDType gBrokerID;         // 模拟经纪商代码
extern TThostFtdcInvestorIDType gInvesterID;     // 投资者账户名
extern TThostFtdcPasswordType gInvesterPassword; // 投资者密码
extern std::function<void(Tick *)> g_pfunMDEventHandlerOnTick;

//全局变量
char *g_pInstrumentID[] = {"rb1801" };				   // 行情合约代码列表
int g_nInstrumentNum = 1;                                          // 行情合约订阅数量


CSimpleMdSpi::~CSimpleMdSpi()
{
}

int CSimpleMdSpi::UserLogin(char *pBrokerID, char *pInverstID, char *pPassWord)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, pBrokerID);
	strcpy(req.UserID, pInverstID);
	strcpy(req.Password, pPassWord);

	int ret = m_pMdUserApi->ReqUserLogin(&req, 0);

	if (!ret)
		cout << ">>>>>>发送登录请求成功" << endl;
	else
		cerr << "--->>>发送登录请求失败" << endl;

	return ret;
}

// ---- ctp_api回调函数 ---- //
// 连接成功应答
void CSimpleMdSpi::OnFrontConnected()
{
	cout << "=====建立网络连接成功=====" << endl;

	//用户登录
	UserLogin(gBrokerID, gInvesterID, gInvesterPassword);
}

// 断开连接通知
void CSimpleMdSpi::OnFrontDisconnected(int nReason)
{
	cerr << "=====网络连接断开=====" << endl;
	cerr << "错误码： " << nReason << endl;
}

// 心跳超时警告
void CSimpleMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "=====网络心跳超时=====" << endl;
	cerr << "距上次连接时间： " << nTimeLapse << endl;
}

// 登录应答
void CSimpleMdSpi::OnRspUserLogin(
	CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		cout << "=====账户登录成功=====" << endl;
		cout << "交易日： " << pRspUserLogin->TradingDay << endl;
		cout << "登录时间： " << pRspUserLogin->LoginTime << endl;
		cout << "经纪商： " << pRspUserLogin->BrokerID << endl;
		cout << "帐户名： " << pRspUserLogin->UserID << endl;
		// 开始订阅行情
		int rt = m_pMdUserApi->SubscribeMarketData(g_pInstrumentID, g_nInstrumentNum);
		if (!rt)
			cout << ">>>>>>发送订阅行情请求成功" << endl;
		else
			cerr << "--->>>发送订阅行情请求失败" << endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 登出应答
void CSimpleMdSpi::OnRspUserLogout(
	CThostFtdcUserLogoutField *pUserLogout,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		cout << "=====账户登出成功=====" << endl;
		cout << "经纪商： " << pUserLogout->BrokerID << endl;
		cout << "帐户名： " << pUserLogout->UserID << endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 错误通知
void CSimpleMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 订阅行情应答
void CSimpleMdSpi::OnRspSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		cout << "=====订阅行情成功=====" << endl;
		cout << "合约代码： " << pSpecificInstrument->InstrumentID << endl;
		cout << "合约代码" << ","
			<< "更新时间" << ","
			<< "最新价" << ","
			<< "成交量" << ","
			<< "买价一" << ","
			<< "买量一" << ","
			<< "卖价一" << ","
			<< "卖量一" << ","
			<< "持仓量" << ","
			<< "换手率"
			<< endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 取消订阅行情应答
void CSimpleMdSpi::OnRspUnSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		cout << "=====取消订阅行情成功=====" << endl;
		cout << "合约代码： " << pSpecificInstrument->InstrumentID << endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 订阅询价应答
void CSimpleMdSpi::OnRspSubForQuoteRsp(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		cout << "=====订阅询价成功=====" << endl;
		cout << "合约代码： " << pSpecificInstrument->InstrumentID << endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 取消订阅询价应答
void CSimpleMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		cout << "=====取消订阅询价成功=====" << endl;
		cout << "合约代码： " << pSpecificInstrument->InstrumentID << endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

// 行情详情通知
void CSimpleMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	// 打印行情
	cout << "=====获得深度行情=====" << endl;
	cout << "交易日： " << pDepthMarketData->TradingDay << endl;
	cout << "交易所代码： " << pDepthMarketData->ExchangeID << endl;
	cout << "合约代码： " << pDepthMarketData->InstrumentID << endl;
	cout << "合约在交易所的代码： " << pDepthMarketData->ExchangeInstID << endl;
	cout << "最新价： " << pDepthMarketData->LastPrice << endl;
	cout << "数量： " << pDepthMarketData->Volume << endl;
	
	if (g_pfunMDEventHandlerOnTick)
	{
		if (pDepthMarketData)
		{
			g_pfunMDEventHandlerOnTick(pDepthMarketData);
		}

	}



	// 取消订阅行情
	//int rt = m_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, g_nInstrumentNum);
	//if (!rt)
	//	cout << ">>>>>>发送取消订阅行情请求成功" << endl;
	//else
	//	cerr << "--->>>发送取消订阅行情请求失败" << endl;
}

// 询价详情通知
void CSimpleMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	// 部分询价结果
	cout << "=====获得询价结果=====" << endl;
	cout << "交易日： " << pForQuoteRsp->TradingDay << endl;
	cout << "交易所代码： " << pForQuoteRsp->ExchangeID << endl;
	cout << "合约代码： " << pForQuoteRsp->InstrumentID << endl;
	cout << "询价编号： " << pForQuoteRsp->ForQuoteSysID << endl;
}
