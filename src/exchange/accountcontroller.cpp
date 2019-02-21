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

	Offer &newOffer = this->offerController_.createBid(accountId, symbol, quantity, price);
	this->exchange_->accounts_[accountId].addOffer(&newOffer);
}

void AccountController::sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	this->validateAccountId(accountId);

	Offer &newOffer = this->offerController_.createAsk(accountId, symbol, quantity, price);
	this->exchange_->accounts_[accountId].addOffer(&newOffer);
}

std::vector<Offer *> &AccountController::getOffers(unsigned int accountId, const std::string &symbol)
{
	this->validateAccountId(accountId);
	this->stockController_.validateStockSymbol(symbol);

	return this->exchange_->accounts_[accountId].getOffers();
}

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
