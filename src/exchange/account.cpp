#include "account.h"

unsigned int Account::accountCounter = 0;

Account::Account()
{
	this->accountId_ = ++accountCounter;
}

void Account::credit(float amount)
{
	this->balance_ += amount;
}

void Account::debit(float amount)
{
	if(this->balance_ < amount){
		throw std::runtime_error("Error: Insufficient funds");
	}
	this->balance_ -= amount;
}

float Account::getBalance()
{
	return this->balance_;
}

void Account::addShares(const std::string &symbol, unsigned int quantity)
{
	this->portfolio_[symbol] += quantity;
}

void Account::removeShares(const std::string &symbol, unsigned int quantity)
{
	if(this->portfolio_[symbol] < quantity){
		throw std::runtime_error("Error: Insufficient shares");
	}
	this->portfolio_[symbol] -= quantity;
}

unsigned int Account::getShares(const std::string &symbol)
{
	if(this->portfolio_.find(symbol) == this->portfolio_.end()){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}
	return this->portfolio_[symbol];
}

unsigned int Account::getId()
{
	return this->accountId_;
}

std::unordered_map<std::string, unsigned int> &Account::getPortfolio()
{
	return this->portfolio_;
}

void Account::addOffer(Offer *offer)
{
	this->offers_[offer->offerId] = offer;
}

float Account::getTotalBidsValue(const std::string &symbol)
{
	float totalValue = 0.0f;

	for(const std::pair<unsigned int, Offer *> &offerPair: this->offers_){
		if(offerPair.second->type_ == Offer::BID){
			totalValue += offerPair.second->price * offerPair.second->quantity;
		}
	}

	return totalValue;
}

unsigned int Account::getTotalAsksSize(const std::string &symbol)
{
	unsigned int totalSize = 0;

	for(const std::pair<unsigned int, Offer *> &offerPair: this->offers_){
		if(offerPair.second->type_ == Offer::ASK){
			totalSize += offerPair.second->price * offerPair.second->quantity;
		}
	}

	return totalSize;
}
