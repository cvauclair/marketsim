#include "stock.h"

std::unordered_map<Stock *, std::mutex> Stock::asksQueueMutexes;
std::unordered_map<Stock *, std::mutex> Stock::bidsQueueMutexes;

Stock::Stock()
{
	// Create mutexes
	Stock::asksQueueMutexes[this];
	Stock::bidsQueueMutexes[this];
}

Stock Stock::create(const std::string &symbol)
{
	Stock newStock;
	newStock.symbol_ = symbol;
	return newStock;
}

std::string &Stock::getSymbol()
{
	return this->symbol_;
}

void Stock::addAsk(unsigned int offerId)
{
	this->lockBidsQueueMutex();
	this->asks_.push_back(offerId);
	this->unlockBidsQueueMutex();
}

void Stock::addBid(unsigned int offerId)
{
	this->lockBidsQueueMutex();
	this->bids_.push_back(offerId);
	this->unlockBidsQueueMutex();
}

std::vector<unsigned int> &Stock::getAsks()
{
	return this->asks_;
}

std::vector<unsigned int> &Stock::getBids()
{
	return this->bids_;
}

void Stock::setLastTradePrice(float lastTradePrice)
{
	this->lastTradePrice_ = lastTradePrice;
}

float Stock::getLastTradePrice()
{
	return this->lastTradePrice_;
}

float Stock::getLowestAskPrice()
{
	return this->lowestAskPrice_;
}

float Stock::getHighestBidPrice()
{
	return this->highestBidPrice_;
}

void Stock::setVolume(unsigned int volume)
{
	this->volume_ = volume;
}

unsigned int Stock::getVolume()
{
	return this->volume_;
}

void Stock::lockAsksQueueMutex()
{
	while(!Stock::asksQueueMutexes[this].try_lock()){}
}

void Stock::unlockAsksQueueMutex()
{
	Stock::asksQueueMutexes[this].unlock();
}

void Stock::lockBidsQueueMutex()
{
	while(!Stock::bidsQueueMutexes[this].try_lock()){}
}

void Stock::unlockBidsQueueMutex()
{
	Stock::bidsQueueMutexes[this].unlock();
}
