#include "tradeinterface.h"

TradeInterface::TradeInterface(Exchange &exchange, Account &account)
{
	this->exchange_ = &exchange;
	this->account_ = &account;
}

void TradeInterface::buy(const std::string &symbol, unsigned int quantity, float price)
{
	// Check if account has enough funds
	if(this->account_->getBalance() < quantity * price){
		throw std::runtime_error("Error: Insufficient funds");
	}

	// Add offer to stock
	Stock &stock = this->exchange_->getStock(symbol);
	stock.addBid(quantity, price, this->account_);
}

void TradeInterface::sell(const std::string &symbol, unsigned int quantity, float price)
{
	// Check if account has enough shares
	if(this->account_->getShares(symbol) < quantity){
		throw std::runtime_error("Error: Insufficient shares");
	}

	// Add offer to currency pair
	Stock &stock = this->exchange_->getStock(symbol);
	stock.addAsk(quantity, price, this->account_);

}

Account &TradeInterface::getAccount()
{
	return *this->account_;
}
