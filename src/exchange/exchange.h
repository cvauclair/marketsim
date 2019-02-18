#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <unordered_map>
#include <utility>

#include "arbitrator.h"
#include "stock.h"
#include "symbols.h"

class Exchange{
	public:
		Exchange();
		~Exchange();

		// Account methods
		Account &createAccount();
		void addShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		void sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		bool validAccounId(unsigned int accountId);

		Stock &getStock(const std::string &symbol);
		bool validStockSymbol(const std::string &symbol);

	private:
		std::unordered_map<std::string, Stock> stocks_;
		std::unordered_map<unsigned int, Account> accounts_;
		std::vector<Arbitrator> arbitrators_;
};

#endif
