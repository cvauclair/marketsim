#include "offercontroller.h"

OfferController::OfferController(Exchange &exchange): sController_(exchange)
{
	this->exchange_ = &exchange;
}

unsigned int OfferController::createAsk(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	// Validate arguments
	this->sController_.validateStockSymbol(symbol);

	// Create new offer
	Offer newOffer(Offer::ASK, symbol, quantity, price, accountId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[newOffer.offerId] = newOffer;
	this->exchange_->unlockOffersMutex();

	this->exchange_->lockStocksMutex();
	this->exchange_->stocks_[symbol].addAsk(newOffer.offerId);
	this->exchange_->unlockStocksMutex();

	// Return newly created offer id
	return newOffer.offerId;
}

unsigned int OfferController::createBid(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	// Validate arguments
	this->sController_.validateStockSymbol(symbol);

	// Create new offer
	Offer newOffer(Offer::BID, symbol, quantity, price, accountId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[newOffer.offerId] = newOffer;
	this->exchange_->unlockOffersMutex();

	this->exchange_->lockStocksMutex();
	this->exchange_->stocks_[symbol].addBid(newOffer.offerId);
	this->exchange_->unlockStocksMutex();

	// Return newly created offer id
	return newOffer.offerId;
}

Offer OfferController::getOfferCopy(unsigned int offerId)
{
	this->validateOfferId(offerId);

	Offer offer;

	this->exchange_->lockOffersMutex();
	offer = this->exchange_->offers_[offerId];
	this->exchange_->unlockOffersMutex();

	return offer;
}

Offer &OfferController::getOffer(unsigned int offerId)
{
	this->validateOfferId(offerId);

	return this->exchange_->offers_[offerId];
}

std::string OfferController::getSymbol(unsigned int offerId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	std::string symbol = this->exchange_->offers_[offerId].symbol_;
	this->exchange_->unlockOffersMutex();

	return symbol;
}

void OfferController::setQuantity(unsigned int offerId, unsigned int quantity)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[offerId].quantity = quantity;
	this->exchange_->unlockOffersMutex();
}

void OfferController::decrementQuantity(unsigned int offerId, unsigned int decrement)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[offerId].quantity -= decrement;
	this->exchange_->unlockOffersMutex();
}

float OfferController::getPrice(unsigned int offerId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	float price = this->exchange_->offers_[offerId].price;
	this->exchange_->unlockOffersMutex();

	return price;
}

void OfferController::setAccountId(unsigned int offerId, unsigned int accountId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[offerId].accountId_ = accountId;
	this->exchange_->unlockOffersMutex();
}

unsigned int OfferController::getAccountId(unsigned int offerId)
{
	this->validateOfferId(offerId);

	unsigned int accountId = 0;

	this->exchange_->lockOffersMutex();
	accountId = this->exchange_->offers_[offerId].accountId_;
	this->exchange_->unlockOffersMutex();

	return accountId;
}

void OfferController::setStatus(unsigned int offerId, Offer::OfferStatus status)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[offerId].status_ = status;
	this->exchange_->unlockOffersMutex();
}

unsigned int OfferController::getQuantity(unsigned int offerId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	unsigned int quantity = this->exchange_->offers_[offerId].quantity;
	this->exchange_->unlockOffersMutex();

	return quantity;
}

Offer::OfferStatus OfferController::getStatus(unsigned int offerId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	Offer::OfferStatus status = this->exchange_->offers_[offerId].status_;
	this->exchange_->unlockOffersMutex();

	return status;
}

void OfferController::setType(unsigned offerId, Offer::OfferType type)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[offerId].type_ = type;
	this->exchange_->unlockOffersMutex();
}

Offer::OfferType OfferController::getType(unsigned int offerId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	Offer::OfferType type =  this->exchange_->offers_[offerId].type_;
	this->exchange_->unlockOffersMutex();

	return type;
}

void OfferController::cancelOffer(unsigned int offerId)
{
	this->validateOfferId(offerId);

	this->exchange_->lockOffersMutex();
	this->exchange_->offers_[offerId].status_ = Offer::CANCELLED;
	this->exchange_->unlockOffersMutex();
}

bool OfferController::comparePrice(unsigned int offerId1, unsigned int offerId2)
{
	this->validateOfferId(offerId1);
	this->validateOfferId(offerId2);

	this->exchange_->lockOffersMutex();
	bool smaller =  this->exchange_->offers_[offerId1].price < this->exchange_->offers_[offerId2].price;
	this->exchange_->unlockOffersMutex();

	return smaller;
}

void OfferController::validateOfferId(unsigned int offerId)
{
	if(!this->validOfferId(offerId)){
		throw std::runtime_error("Error: Invalid offer id " + std::to_string(offerId));
	}
}

bool OfferController::validOfferId(unsigned int offerId)
{
	this->exchange_->lockOffersMutex();
	bool valid = this->exchange_->offers_.find(offerId) != this->exchange_->offers_.end();
	this->exchange_->unlockOffersMutex();

	if(valid){
		return true;
	}

	return false;
}
