#include "offercontroller.h"

OfferController::OfferController(Exchange &exchange): sController_(exchange)
{
	this->exchange_ = &exchange;
}

Offer &OfferController::createAsk(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	// Validate arguments
	this->sController_.validateStockSymbol(symbol);

	// Create new offer
	Offer newOffer(Offer::ASK, quantity, price, &(this->exchange_->accounts_[accountId]));
	this->exchange_->stocks_[symbol].addAsk(newOffer);

	// Return newly created offer
	return this->exchange_->stocks_[symbol].getAsks().back();
}

Offer &OfferController::createBid(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	// Validate arguments
	this->sController_.validateStockSymbol(symbol);

	// Create new offer
	Offer newOffer(Offer::BID, quantity, price, &(this->exchange_->accounts_[accountId]));
	this->exchange_->stocks_[symbol].addBid(newOffer);

	// Return newly created offer
	return this->exchange_->stocks_[symbol].getBids().back();
}

void OfferController::cancelOffer(unsigned int offerId)
{
	
}

std::vector<Offer *> OfferController::getAccountOffers(unsigned int accountId, const std::string &symbol)
{
	std::vector<Offer *> offers;

	if(!this->sController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	Stock &stock = this->exchange_->stocks_[symbol];
}
