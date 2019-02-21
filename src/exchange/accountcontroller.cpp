#include "accountcontroller.h"

AccountController::AccountController(Exchange &exchange): stockController_(exchange)
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
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->stockController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->exchange_->accounts_[accountId].addShares(symbol, quantity);
}

void AccountController::removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->stockController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->exchange_->accounts_[accountId].removeShares(symbol, quantity);
}

void AccountController::buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->stockController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->exchange_->stocks_[symbol].addBid(quantity, price, &(this->exchange_->accounts_[accountId]));
}

void AccountController::sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->stockController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->exchange_->stocks_[symbol].addAsk(quantity, price, &(this->exchange_->accounts_[accountId]));
}

std::vector<Offer *> &AccountController::getOffers(unsigned int accountId, const std::string &symbol)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->stockController_.validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	return this->exchange_->accounts_[accountId].getOffers();
}

void AccountController::cancelOffer(unsigned int offerId)
{

}

bool AccountController::validAccounId(unsigned int accountId)
{
	if(this->exchange_->accounts_.find(accountId) != this->exchange_->accounts_.end()){
		return true;
	}
	return false;
}
