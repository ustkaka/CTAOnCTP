#include "stdafx.h"
#include "SimpleStrategy.h"
#include <iostream>
#include <cstring>

enum POSITION_DIRECTION :int {
	SHORT_POSITION = -1,
	EMPTY_POSITION = 0,
	LONG_POSITION = 1
};

CSimpleStrategy::CSimpleStrategy(CSimpleTraderSpi *pTraderSpi,
	std::string strTradeInstrument,
	double dAtrRatio)
	: m_pTraderSpi(pTraderSpi)
	, m_strTradeInstrument(strTradeInstrument)
	, m_dAtrRatio(dAtrRatio)
	, m_dBreakHighPrice(1000000.0)
	, m_dBreakLowPrice(-1000000.0)
	, m_nPositionDriection(EMPTY_POSITION)
{
	memset(&m_CurrentTick, 0, sizeof(m_CurrentTick));
	memset(&m_PreviousTick, 0, sizeof(m_PreviousTick));
}


CSimpleStrategy::~CSimpleStrategy()
{
}


//Tick中实现策略的主逻辑
//上轨 = 开盘价格 * （1 + AtrRatio）
//下轨 = 开盘价格 * （1 - AtrRatio）	// AtrRatio 为振幅参数
//
//A = Tick的LastPrice
//无仓位，A突破上轨。开多仓
//无仓位，A突破下轨。开空仓
//
//多仓，A突破上轨。无操作
//多仓，A突破下轨。平多仓，开空仓
//
//空仓，A突破上轨。平空仓，开空仓
//空仓，A突破下轨。无操作
void CSimpleStrategy::OnTick(Tick *pTick)
{
	//过滤非交易合约的行情
	if(strcmp(m_strTradeInstrument.c_str(),pTick->InstrumentID))
	{ 
		return;
	}

	m_PreviousTick = m_CurrentTick;
	m_CurrentTick = *pTick;

	if (m_PreviousTick.LastPrice < 0.001 || trading_day_not_same(&m_CurrentTick, &m_PreviousTick))
	{
		//开盘
		OnDayOpen();
	}

	if (EMPTY_POSITION == m_nPositionDriection)
	{
		if (m_CurrentTick.LastPrice > m_dBreakHighPrice)
		{
			//无仓位，A突破上轨。开多仓
			std::cout << "空仓，A突破上轨。开多仓" << std::endl;
			
			m_nPositionDriection = LONG_POSITION;
			m_pTraderSpi->reqOrderInsert((char *)m_strTradeInstrument.c_str(),
										m_CurrentTick.AskPrice1, 
										1, 
										THOST_FTDC_DEN_Buy, //买
										THOST_FTDC_OF_Open);//开
		}

		if (m_CurrentTick.LastPrice < m_dBreakLowPrice)
		{
			//无仓位，突破下轨。开空仓
			std::cout << "空仓，突破下轨。开空仓" << std::endl;

			m_nPositionDriection = SHORT_POSITION;
			m_pTraderSpi->reqOrderInsert((char *)m_strTradeInstrument.c_str(),
										m_CurrentTick.BidPrice1,
										1,
										THOST_FTDC_DEN_Sell,//卖
										THOST_FTDC_OF_Open);//开
		}

	}
	
	if (LONG_POSITION == m_nPositionDriection)
	{
		if (m_CurrentTick.LastPrice < m_dBreakLowPrice)
		{
			//多仓，A突破下轨。平多仓，开空仓
			std::cout << "多仓，A突破下轨。平多仓，开空仓" << std::endl;

			m_nPositionDriection = SHORT_POSITION;
			//平多仓
			m_pTraderSpi->reqOrderInsert((char *)m_strTradeInstrument.c_str(),
										m_CurrentTick.BidPrice1,
										1,
										THOST_FTDC_DEN_Sell,//卖
										THOST_FTDC_OF_Close);//平
			//开空仓
			m_pTraderSpi->reqOrderInsert((char *)m_strTradeInstrument.c_str(),
										m_CurrentTick.BidPrice1,
										1,
										THOST_FTDC_DEN_Sell,//卖
										THOST_FTDC_OF_Open);//开

		}
	}

	if (SHORT_POSITION == m_nPositionDriection)
	{
		if (m_CurrentTick.LastPrice > m_dBreakHighPrice)
		{
			//空仓，A突破上轨。平空仓，开多仓
			std::cout << "空仓，A突破上轨。平空仓，开空仓" << std::endl;

			m_nPositionDriection = LONG_POSITION;
			//平空仓
			m_pTraderSpi->reqOrderInsert((char *)m_strTradeInstrument.c_str(),
				m_CurrentTick.AskPrice1,
				1,
				THOST_FTDC_D_Buy,//买
				THOST_FTDC_OF_Close);//平
			//开多仓
			m_pTraderSpi->reqOrderInsert((char *)m_strTradeInstrument.c_str(),
				m_CurrentTick.AskPrice1,
				1,
				THOST_FTDC_D_Buy,//买
				THOST_FTDC_OF_Open);//开

		}

	}

}

void CSimpleStrategy::OnDayOpen()
{
	//计算上下轨
	m_dBreakHighPrice = m_CurrentTick.LastPrice * (1.0 + m_dAtrRatio);
	std::cout << "上轨: " << m_dBreakHighPrice << std::endl;

	m_dBreakLowPrice = m_CurrentTick.LastPrice * (1.0 - m_dAtrRatio);
	std::cout << "下轨: " << m_dBreakLowPrice << std::endl;
}

bool CSimpleStrategy::trading_day_not_same(Tick *pTick1, Tick *pTick2)
{
	if (strcmp(pTick1->TradingDay, pTick2->TradingDay) == 0)
	{
		return false;
	}

	return true;
}
