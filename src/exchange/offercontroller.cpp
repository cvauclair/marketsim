#include "offercontroller.h"

OfferController::OfferController(Exchange &exchange): sController_(exchange)
{
	this->exchange_ = &exchange;
}

std::vector<Offer *> OfferController::getAccountOffers(unsigned int accountId, const std::string &symbol)
{
	std::vector<Offer *> offers;

	if(!this->sController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	Stock &stock = this->exchange_->stocks_[symbol];
}
