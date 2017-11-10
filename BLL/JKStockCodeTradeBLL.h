#pragma once


#include "BLL/JKBaseBLL.h"
#include "Model/JKStockCodeTradeModel.h"


class JKStockCodeTradeBLL : public JKBaseBLL
{
	friend class JKStockCodeBLL;

	JK_BLL_INIT(JKStockCodeTrade);

public:
	/**
	 *	 设置参数
	 */
	void setParams(TradeType type, JKString date, JKUInt64 count, double buyPrice);
	/** 
	 *	卖出
	 */
	void sell(double price);

	TradeType getType();
	JKString getDate();
	JKUInt64 getCount();
	double getBuyPrice();
	double getSellPrice();
	double getSumPrice();

	/** 
	 *	获取买卖利润差，不包括额外的税费
	 */
	double getPureEarning(const double & latestPrice);
	double getPureEarningPercent(const double & latestPrice);

};


