#include "tradeinterface.h"

TradeInterface::TradeInterface(Exchange &exchange, Account &account)
{
	this->exchange_ = &exchange;
	this->account_ = &account;
}

TradeInterface TradeInterface::create(Exchange &exchange, Account &account)
{
	TradeInterface newTradeInterface(exchange, account);
	return newTradeInterface;
}

void TradeInterface::buy(const std::string &symbol, unsigned int quantity, float price)
{
	// Check if account has enough funds
	if(this->account_->getBalance() < quantity * price){
		throw std::runtime_error("Error: Insufficient funds");
	}

	// Add offer to stock
	this->exchange_->buyShares(this->account_->getId(), symbol, quantity, price);
}

void TradeInterface::sell(const std::string &symbol, unsigned int quantity, float price)
{
	// Check if account has enough shares
	if(this->account_->getShares(symbol) < quantity){
		throw std::runtime_error("Error: Insufficient shares");
	}

	// Add offer to currency pair
	this->exchange_->sellShares(this->account_->getId(), symbol, quantity, price);
}

Account &TradeInterface::getAccount()
{
	return *this->account_;
}
