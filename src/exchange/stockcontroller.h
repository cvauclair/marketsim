#ifndef STOCKCONTROLLER_H
#define STOCKCONTROLLER_H

#include "exchange.h"

class StockController{
	public:
		StockController(Exchange &exchange);

		Stock &getStock(const std::string &symbol);

		std::vector<unsigned int> getAsks(const std::string &symbol);
		std::vector<unsigned int> getBids(const std::string &symbol);

		void setLastTradePrice(const std::string &symbol, float lastTradePrice);
		float getLastTradePrice(const std::string &symbol);

		float getHighestBid(const std::string &symbol);
		float getLowestAsk(const std::string &symbol);

		void setVolume(const std::string &symbol, unsigned int volume);
		void incrementVolume(const std::string &symbol, unsigned int volume);
		unsigned int getVolume(const std::string &symbol);

		// This methods will throw an exception if the stock symbol is invalid
		// and will do nothing otherwise
		void validateStockSymbol(const std::string &symbol);

		// This method returns true if the stock symbol is valid and false if it is invalid.
		// A valid stock symbol means that it is in the hashtable of the exchange.
		bool validStockSymbol(const std::string &symbol);

	private:
		Exchange *exchange_ = nullptr;
};

#endif
