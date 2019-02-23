#include "offer.h"

unsigned int Offer::offerCounter = 0;

Offer::Offer(OfferType type, const std::string &symbol, unsigned int quantity, float price, unsigned int accountId)
{
	this->offerId = ++offerCounter;

	this->symbol_ = symbol;
	this->quantity = quantity;
	this->price = price;
	this->accountId_ = accountId;
	this->status_ = Offer::PENDING;
	this->type_ = type;

}
