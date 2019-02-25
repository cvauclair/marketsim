#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <unordered_map>
#include <utility>
#include <mutex>

#include "account.h"
#include "stock.h"
#include "symbols.h"

#include "configloader.h"

#include "logger.h"

// The Exchange class acts as a controller for the whole system
class Exchange{
	friend class AccountController;
	friend class MarketController;
	friend class OfferController;
	friend class StockController;
	public:
		Exchange();
		~Exchange();

		void lockAccountsMutex();
		void unlockAccountsMutex();

		void lockStocksMutex();
		void unlockStocksMutex();

		void lockOffersMutex();
		void unlockOffersMutex();

		void clear();

	private:
		// Mutex
		static std::mutex accountsMutex_;
		static std::mutex stocksMutex_;
		static std::mutex offersMutex_;

		// Accounts
		std::unordered_map<unsigned int, Account> accounts_;

		// Stocks
		std::unordered_map<std::string, Stock> stocks_;

		// Offers
		std::unordered_map<unsigned int, Offer> offers_;
		unsigned int offerCounter_ = 0;

		// House account
		Account *exchangeAccount_ = nullptr;
};

#endif
