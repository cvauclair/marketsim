#include "stockcontroller.h"

StockController::StockController(Exchange &exchange)
{
	this->exchange_ = &exchange;
}

Stock StockController::getStockCopy(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	Stock stock;

	this->exchange_->lockStocksMutex();
	stock = this->exchange_->stocks_[symbol];
	this->exchange_->unlockStocksMutex();

	return stock;
}

void StockController::addAsk(const std::string &symbol, unsigned int offerId)
{

}

std::vector<unsigned int> StockController::getAsks(const std::string &symbol)
{
	this->validStockSymbol(symbol);

	std::vector<unsigned int> asks;

	this->exchange_->lockStocksMutex();
	asks = this->exchange_->stocks_[symbol].getAsks();
	this->exchange_->unlockStocksMutex();

	return  asks;
}

void StockController::addBid(const std::string &symbol, unsigned int offerId)
{

}

std::vector<unsigned int> StockController::getBids(const std::string &symbol)
{
	this->validStockSymbol(symbol);

	std::vector<unsigned int> bids;

	this->exchange_->lockStocksMutex();
	bids = this->exchange_->stocks_[symbol].getBids();
	this->exchange_->unlockStocksMutex();

	return  bids;
}

void StockController::setLastTradePrice(const std::string &symbol, float lastTradePrice)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	this->exchange_->stocks_[symbol].setLastTradePrice(lastTradePrice);
	this->exchange_->unlockStocksMutex();
}

float StockController::getLastTradePrice(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	float lastTradePrice = this->exchange_->stocks_[symbol].getLastTradePrice();
	this->exchange_->unlockStocksMutex();

	return lastTradePrice;
}

void StockController::setVolume(const std::string &symbol, unsigned int volume)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	this->exchange_->stocks_[symbol].setVolume(volume);
	this->exchange_->unlockStocksMutex();
}

void StockController::incrementVolume(const std::string &symbol, unsigned int increment)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	this->exchange_->stocks_[symbol].setVolume(this->exchange_->stocks_[symbol].getVolume() + increment);
	this->exchange_->unlockStocksMutex();
}

float StockController::getHighestBid(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	float highestBidPrice = this->exchange_->stocks_[symbol].getHighestBidPrice();
	this->exchange_->unlockStocksMutex();

	return highestBidPrice;
}

float StockController::getLowestAsk(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	float lowestAskPrice = this->exchange_->stocks_[symbol].getLowestAskPrice();
	this->exchange_->unlockStocksMutex();

	return lowestAskPrice;
}

unsigned int StockController::getVolume(const std::string &symbol)
{
	this->validateStockSymbol(symbol);

	this->exchange_->lockStocksMutex();
	unsigned int volume = this->exchange_->stocks_[symbol].getVolume();
	this->exchange_->unlockStocksMutex();

	return volume;
}

void StockController::validateStockSymbol(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}
}

bool StockController::validStockSymbol(const std::string &symbol)
{
	this->exchange_->lockStocksMutex();
	bool valid = this->exchange_->stocks_.find(symbol) != this->exchange_->stocks_.end();
	this->exchange_->unlockStocksMutex();

	if(valid){
		return true;
	}
	return false;
}
