#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <unordered_map>
#include <utility>

#include "arbitrator.h"
#include "stock.h"
#include "symbols.h"

// The Exchange class acts as a controller for the whole system
class Exchange{
	public:
		Exchange();
		~Exchange();

		// Start
		void start();

		// Account methods
		Account &createAccount();
		void addShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		void sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		bool validAccounId(unsigned int accountId);

		// Stock methods
		Stock &getStock(const std::string &symbol);
		float getLastTradePrice(const std::string &symbol);
		float getHighestBid(const std::string &symbol);
		float getLowestAsk(const std::string &symbol);
		bool validStockSymbol(const std::string &symbol);

	private:
		std::unordered_map<std::string, Stock> stocks_;
		std::unordered_map<unsigned int, Account> accounts_;
		std::vector<Arbitrator> arbitrators_;
};

#endif
