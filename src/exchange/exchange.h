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
	friend class OfferController;
	friend class StockController;
	public:
		Exchange();
		~Exchange();

		// Start
		void start();

	private:
		std::unordered_map<std::string, Stock> stocks_;
		std::unordered_map<unsigned int, Account> accounts_;
		std::vector<Arbitrator> arbitrators_;
		std::vector<Offer> offers_;

		Account *exchangeAccount_ = nullptr;
};

#endif
