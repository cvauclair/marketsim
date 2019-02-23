#include "accountcontroller.h"

AccountController::AccountController(Exchange &exchange): offerController_(exchange), stockController_(exchange)
{
	this->exchange_ = &exchange;
}

Account &AccountController::createAccount()
{
	Account newAccount;
	this->exchange_->accounts_[newAccount.getId()] = newAccount;
	return this->exchange_->accounts_[newAccount.getId()];
}

void AccountController::addShares(unsigned int accountId, const std::string &symbol, unsigned int quantity)
{
	this->validateAccountId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	this->exchange_->accounts_[accountId].addShares(symbol, quantity);
}

void AccountController::removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity)
{
	this->validateAccountId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	this->exchange_->accounts_[accountId].removeShares(symbol, quantity);
}

void AccountController::buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	this->validateAccountId(accountId);

	// Check if enough funds
	this->exchange_->lockAccountsMutex();
	float balance = this->exchange_->accounts_[accountId].getBalance();
	this->exchange_->unlockAccountsMutex();

	if(this->getTotalBidsValue(accountId, symbol) + quantity * price > balance){
		throw std::runtime_error("Error: Insufficient funds");
	}

	Offer *newOffer = this->offerController_.createBid(accountId, symbol, quantity, price);
	this->exchange_->accounts_[accountId].addOffer(newOffer->offerId);

	Logger::log("info", "Offer " + std::to_string(newOffer->offerId) + ": Buy " + std::to_string(quantity) + " " + symbol + " @ " + std::to_string(price), true);
}

void AccountController::sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	this->validateAccountId(accountId);

	// Check if enough shares
	this->exchange_->lockAccountsMutex();
	unsigned int numShares = this->exchange_->accounts_[accountId].getShares(symbol);
	this->exchange_->unlockAccountsMutex();

	if(this->getTotalAsksSize(accountId, symbol) + quantity > numShares){
		throw std::runtime_error("Error: Insufficient shares " + symbol);
	}

	Offer *newOffer = this->offerController_.createAsk(accountId, symbol, quantity, price);
	this->exchange_->accounts_[accountId].addOffer(newOffer->offerId);

	Logger::log("info", "Offer " + std::to_string(newOffer->offerId) + ": Sell " + std::to_string(quantity) + " " + symbol + " @ " + std::to_string(price), true);
}

float AccountController::getTotalBidsValue(unsigned int accountId, const std::string &symbol)
{
	this->validAccounId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	this->exchange_->lockOffersMutex();
	std::vector<unsigned int> pendingOffersIds = this->exchange_->accounts_[accountId].getPendingOffersId();
	this->exchange_->unlockOffersMutex();

	unsigned int totalValue = 0;
	for(unsigned int offerId: pendingOffersIds){
		if(this->offerController_.getType(offerId) == Offer::ASK){
			totalValue += this->offerController_.getQuantity(offerId) * this->offerController_.getPrice(offerId);
		}
	}

	return totalValue;
}

unsigned int AccountController::getTotalAsksSize(unsigned int accountId, const std::string &symbol)
{
	this->validAccounId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	this->exchange_->lockOffersMutex();
	std::vector<unsigned int> pendingOffersIds = this->exchange_->accounts_[accountId].getPendingOffersId();
	this->exchange_->unlockOffersMutex();

	unsigned int asksSize = 0;
	for(unsigned int offerId: pendingOffersIds){
		if(this->offerController_.getType(offerId) == Offer::ASK){
			asksSize += this->offerController_.getQuantity(offerId);
		}
	}

	return asksSize;
}

std::vector<unsigned int> AccountController::getPendingOffers(unsigned int accountId, const std::string &symbol)
{
	this->validateAccountId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	this->exchange_->lockOffersMutex();
	std::vector<unsigned int> offerIds = this->exchange_->accounts_[accountId].getPendingOffersId();
	this->exchange_->unlockOffersMutex();

	return offerIds;
}

//std::vector<Offer *> &AccountController::getOffers(unsigned int accountId, const std::string &symbol)
//{
//	this->validateAccountId(accountId);
//	this->stockController_.validateStockSymbol(symbol);

//	return this->exchange_->accounts_[accountId].getOffers();
//}

void AccountController::cancelOffer(unsigned int offerId)
{
	this->offerController_.cancelOffer(offerId);
}

void AccountController::validateAccountId(unsigned int accountId)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}
}

bool AccountController::validAccounId(unsigned int accountId)
{
	if(this->exchange_->accounts_.find(accountId) != this->exchange_->accounts_.end()){
		return true;
	}
	return false;
}
