#ifndef OFFERCONTROLLER_H
#define OFFERCONTROLLER_H

#include "exchange.h"
#include "stockcontroller.h"

class OfferController{
	public:
		OfferController(Exchange &exchange);

		Offer &createAsk(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price);
		Offer &createBid(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price);

		void cancelOffer(unsigned int offerId);

		std::vector<Offer *> getAccountOffers(unsigned int accountId, const std::string &symbol);

		float getLowestAskPrice(const std::string &symbol);
		float getHighestBidPrice(const std::string &symbol);

	private:
		StockController sController_;
		Exchange *exchange_ = nullptr;
};

#endif
