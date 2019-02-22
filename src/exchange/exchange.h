#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <unordered_map>
#include <utility>

#include "account.h"
#include "arbitrator.h"
#include "stock.h"
#include "symbols.h"

// The Exchange class acts as a controller for the whole system
class Exchange{
	friend class AccountController;
	friend class MarketController;
	friend class OfferController;
	friend class StockController;
	public:
		Exchange();
		~Exchange();

		// Start
		void start();

	private:
		// Accounts
		std::unordered_map<unsigned int, Account> accounts_;

		// Stocks
		std::unordered_map<std::string, Stock> stocks_;
		std::vector<ExchangeWorker> arbitrators_;

		// Offers
		unsigned int offerCounter_ = 0;

		// House account
		Account *exchangeAccount_ = nullptr;
};

#endif
