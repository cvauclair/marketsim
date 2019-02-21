#ifndef STOCKCONTROLLER_H
#define STOCKCONTROLLER_H

#include "exchange.h"

class StockController{
	public:
		StockController(Exchange &exchange);

		Stock &getStock(const std::string &symbol);

		float getLastTradePrice(const std::string &symbol);
		float getHighestBid(const std::string &symbol);
		float getLowestAsk(const std::string &symbol);

		unsigned int getVolume(const std::string &symbol);

		bool validStockSymbol(const std::string &symbol);

	private:
		Exchange *exchange_ = nullptr;
};

#endif
