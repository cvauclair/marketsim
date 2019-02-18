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
	try {
		this->portfolio_.at(symbol) += quantity;
	} catch (std::exception &e) {
		throw std::runtime_error("Error: Invalid currency symbol " + symbol);
	}
}

void Account::removeShares(const std::string &symbol, unsigned int quantity)
{
	if(this->portfolio_.find(symbol) != this->portfolio_.end()){
		if(this->portfolio_.at(symbol) >= quantity){
			this->portfolio_.at(symbol) -= quantity;
		}else {
			throw std::runtime_error("Error: Insufficient funds");
		}
	}else{
		throw std::runtime_error("Error: Invalid currency symbol " + symbol);
	}
}

unsigned int Account::getShares(const std::string &symbol)
{
	if(this->portfolio_.find(symbol) == this->portfolio_.end()){
		throw std::runtime_error("Error: Invalid currency symbol " + symbol);
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
