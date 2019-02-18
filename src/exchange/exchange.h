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

		Account &createAccount();

		Stock &getStock(const std::string &symbol);

	private:
		std::unordered_map<std::string, Stock> stocks_;
		std::unordered_map<unsigned int, Account> accounts_;
		std::vector<Arbitrator> arbitrators_;
};

#endif
