#ifndef MARKETCONTROLLER_H
#define MARKETCONTROLLER_H

#include <algorithm>
#include <vector>
#include <functional>

#include "exchange.h"
#include "accountcontroller.h"
#include "offercontroller.h"
#include "stockcontroller.h"

class MarketController{
	public:
		MarketController(Exchange &exchange);

		std::vector<unsigned int> getSortedAsks(const std::string &symbol);
		std::vector<unsigned int> getSortedBids(const std::string &symbol);

		// Helper methods to sort offers in ascending/descending order
		void sortAscendingOrder(std::vector<unsigned int> &offerIds);
		void sortDescendingOrder(std::vector<unsigned int> &offerIds);

		void resolveOffers(const std::string &symbol);
		void executeTrade(const std::string &symbol, unsigned int askId, unsigned int bidId);

	private:
		Exchange *exchange_ = nullptr;
		AccountController accountController_;
		OfferController offerController_;
		StockController stockController_;
};

#endif
