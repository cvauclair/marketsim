#include "stockcontroller.h"

StockController::StockController(Exchange &exchange)
{
	this->exchange_ = &exchange;
}

Stock &StockController::getStock(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	return this->exchange_->stocks_[symbol];
}

float StockController::getLastTradePrice(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	return this->exchange_->stocks_[symbol].getLastTradePrice();
}

float StockController::getHighestBid(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	return this->exchange_->stocks_[symbol].getHighestBidPrice();
}

float StockController::getLowestAsk(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	return this->exchange_->stocks_[symbol].getLowestAskPrice();
}

unsigned int StockController::getVolume(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	return this->exchange_->stocks_[symbol].getVolume();
}

void StockController::validateStockSymbol(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}
}

bool StockController::validStockSymbol(const std::string &symbol)
{
	if(this->exchange_->stocks_.find(symbol) != this->exchange_->stocks_.end()){
		return true;
	}
	return false;
}
