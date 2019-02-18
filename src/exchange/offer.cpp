#include "offer.h"

unsigned int Offer::offerCounter = 0;

Offer::Offer(unsigned int quantity, float price, Account *account)
{
	this->quantity = quantity;
	this->price = price;
	this->account = account;

	this->offerId = ++offerCounter;
}
