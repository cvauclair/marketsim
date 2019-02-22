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

std::vector<Offer> &StockController::getAsks(const std::string &symbol)
{
	this->validStockSymbol(symbol);

	return  this->exchange_->stocks_[symbol].getAsks();
}

std::vector<Offer> &StockController::getBids(const std::string &symbol)
{
	this->validStockSymbol(symbol);

	return  this->exchange_->stocks_[symbol].getBids();
}

void StockController::setLastTradePrice(const std::string &symbol, float lastTradePrice)
{
	this->validateStockSymbol(symbol);

	this->exchange_->stocks_[symbol].setLastTradePrice(lastTradePrice);
}

float StockController::getLastTradePrice(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	return this->exchange_->stocks_[symbol].getLastTradePrice();
}

void StockController::setVolume(const std::string &symbol, unsigned int volume)
{
	this->validateStockSymbol(symbol);

	this->exchange_->stocks_[symbol].setVolume(volume);
}

void StockController::incrementVolume(const std::string &symbol, unsigned int increment)
{
	this->validateStockSymbol(symbol);

	this->exchange_->stocks_[symbol].setVolume(this->exchange_->stocks_[symbol].getVolume() + increment);
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
