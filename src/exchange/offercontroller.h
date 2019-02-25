#ifndef OFFERCONTROLLER_H
#define OFFERCONTROLLER_H

#include "exchange.h"
#include "stockcontroller.h"

class OfferController{
	public:
		OfferController(Exchange &exchange);

		unsigned int createAsk(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price);
		unsigned int createBid(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price);

		// Returns a COPY of the Offer object associated with offerId (if valid)
		Offer getOfferCopy(unsigned int offerId);

		std::string getSymbol(unsigned int offerId);
		unsigned int getQuantity(unsigned int offerId);
		float getPrice(unsigned int offerId);
		Offer::OfferStatus getStatus(unsigned int offerId);
		Offer::OfferType getType(unsigned int offerId);

		void cancelOffer(unsigned int offerId);

		float getLowestAskPrice(const std::string &symbol);
		float getHighestBidPrice(const std::string &symbol);

		// Returns true if first offer is priced lower than second offer
		bool comparePrice(unsigned int offerId1, unsigned int offerId2);

		void validateOfferId(unsigned int offerId);
		bool validOfferId(unsigned int offerId);

		struct AscendingOrderPriceComparator;
		struct DescendingOrderPriceComparator;

		Offer &getOffer(unsigned int offerId);

	private:
		StockController sController_;
		Exchange *exchange_ = nullptr;
};

struct OfferController::AscendingOrderPriceComparator{
	AscendingOrderPriceComparator(Exchange &exchange): offerController_(exchange){}

	bool operator()(unsigned int offerId1, unsigned int offerId2){
		return this->offerController_.getPrice(offerId1) < this->offerController_.getPrice(offerId2);
	}

	OfferController offerController_;
};

struct OfferController::DescendingOrderPriceComparator{
	DescendingOrderPriceComparator(Exchange &exchange): offerController_(exchange){}

	bool operator()(unsigned int offerId1, unsigned int offerId2){
		return this->offerController_.getPrice(offerId1) > this->offerController_.getPrice(offerId2);
	}

	OfferController offerController_;
};

#endif
