#ifndef OFFER_H
#define OFFER_H

#include <string>
#include <math.h>

#define CURRENT 0.0

// The Offer class represents a bid or ask offer for a certain currency.
// The desired currency in question (as well as the currency that will be used
// to buy the latter) are implicitely determined from the CurrencyPair in which
// the Offer is stored, as well as wether it is in the bids queue or the ask queue
class Account;
class Offer{
	public:
		enum OfferStatus{PENDING, PROCESSING, FULFILLED, CANCELLED};
		enum OfferType{ASK, BID};

		Offer(){}
		Offer(OfferType type, const std::string &symbol, unsigned int quantity, float price, unsigned int accountId);

		unsigned int offerId = 0;

		std::string symbol_ = "";
		unsigned int quantity = 0;
		float price = 0.0;
		unsigned int accountId_ = 0;
		OfferStatus status_;
		OfferType type_;

	static unsigned int offerCounter;
	static float round(float price);
};

#endif
