#ifndef MARKETCONTROLLER_H
#define MARKETCONTROLLER_H

#include <set>

#include "exchange.h"
#include "accountcontroller.h"
#include "offercontroller.h"
#include "stockcontroller.h"

class MarketController{
	public:
		MarketController(Exchange &exchange);

		std::set<Offer *, bool (*)(Offer *, Offer *)> getAsks(const std::string &symbol);
		std::set<Offer *, bool (*)(Offer *, Offer *)> getBids(const std::string &symbol);

		void resolveOffers(const std::string &symbol);
		void executeTrade(const std::string &symbol, Offer *ask, Offer *bid);

	private:
		Exchange *exchange_ = nullptr;
		AccountController accountController_;
		OfferController offerController_;
		StockController stockController_;
};

#endif
