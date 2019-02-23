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
	if(this->getTotalBidsValue(accountId, symbol) + quantity * price > this->exchange_->accounts_[accountId].getBalance()){
		throw std::runtime_error("Error: Insufficient funds");
	}

	Offer *newOffer = this->offerController_.createBid(accountId, symbol, quantity, price);
	this->exchange_->accounts_[accountId].addOffer(newOffer);

	Logger::log("info", "Offer " + std::to_string(newOffer->offerId) + ": Buy " + std::to_string(quantity) + " " + symbol + " @ " + std::to_string(price), true);
}

void AccountController::sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	this->validateAccountId(accountId);

	// Check if enough shares
	if(this->getTotalAsksSize(accountId, symbol) + quantity > this->exchange_->accounts_[accountId].getShares(symbol)){
		throw std::runtime_error("Error: Insufficient shares " + symbol);
	}

	Offer *newOffer = this->offerController_.createAsk(accountId, symbol, quantity, price);
	this->exchange_->accounts_[accountId].addOffer(newOffer);

	Logger::log("info", "Offer " + std::to_string(newOffer->offerId) + ": Sell " + std::to_string(quantity) + " " + symbol + " @ " + std::to_string(price), true);
}

float AccountController::getTotalBidsValue(unsigned int accountId, const std::string &symbol)
{
	this->validAccounId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	return this->exchange_->accounts_[accountId].getTotalBidsValue(symbol);
}

unsigned int AccountController::getTotalAsksSize(unsigned int accountId, const std::string &symbol)
{
	this->validAccounId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	return this->exchange_->accounts_[accountId].getTotalAsksSize(symbol);
}

//std::vector<Offer *> &AccountController::getOffers(unsigned int accountId, const std::string &symbol)
//{
//	this->validateAccountId(accountId);
//	this->stockController_.validateStockSymbol(symbol);

//	return this->exchange_->accounts_[accountId].getOffers();
//}

void AccountController::cancelOffer(unsigned int offerId)
{

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
