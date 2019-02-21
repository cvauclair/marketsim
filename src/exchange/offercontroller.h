#ifndef OFFERCONTROLLER_H
#define OFFERCONTROLLER_H

#include "exchange.h"
#include "stockcontroller.h"

class OfferController{
	public:
		OfferController(Exchange &exchange);



		std::vector<Offer *> getAccountOffers(unsigned int accountId, const std::string &symbol);

	private:
		StockController sController_;
		Exchange *exchange_ = nullptr;
};

#endif
