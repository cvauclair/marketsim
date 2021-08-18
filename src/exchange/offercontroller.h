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

		// Get and set stock symbol
		std::string getSymbol(unsigned int offerId);

		// Get and set quantity
		void setQuantity(unsigned int offerId, unsigned int quantity);
		void decrementQuantity(unsigned int offerId, unsigned int decrement);
		unsigned int getQuantity(unsigned int offerId);

		// Get and set price
		float getPrice(unsigned int offerId);

		// Get and set account id
		void setAccountId(unsigned int offerId, unsigned int accountId);
		unsigned int getAccountId(unsigned int offerId);

		// Get and set status
		void setStatus(unsigned int offerId, Offer::OfferStatus status);
		Offer::OfferStatus getStatus(unsigned int offerId);

		// Get and set type
		void setType(unsigned offerId, Offer::OfferType type);
		Offer::OfferType getType(unsigned int offerId);

		// Cancel offer
		void cancelOffer(unsigned int offerId);

		// Get lowest ask price offer for specific stock symbol
		float getLowestAskPrice(const std::string &symbol);

		// Get highest bid price offer for specific stock symbol
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

#endif
