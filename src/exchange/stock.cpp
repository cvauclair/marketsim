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

void Stock::addAsk(unsigned int quantity, float price, Account *account)
{
	this->lockAsksQueueMutex();
	this->asksQueue_.emplace_back(quantity, price, account);
	this->unlockAsksQueueMutex();

	Logger::log("info", "Offer " + std::to_string(Offer::offerCounter) + ": Sell " + std::to_string(quantity) + " " + this->getSymbol() + " @ " + std::to_string(price), true);
}

void Stock::addBid(unsigned int quantity, float price, Account *account)
{
	this->lockBidsQueueMutex();
	this->bidsQueue_.emplace_back(quantity, price, account);
	this->unlockBidsQueueMutex();

	Logger::log("info", "Offer " + std::to_string(Offer::offerCounter) + ": Buy " + std::to_string(quantity) + " " + this->getSymbol() + " @ " + std::to_string(price), true);
}

std::vector<Offer> &Stock::getAsks()
{
	this->lockAsksQueueMutex();

	// Transfer asks
	this->asks_.insert(this->asks_.end(), this->asksQueue_.begin(), this->asksQueue_.end());
	this->asksQueue_.clear();

	this->unlockAsksQueueMutex();

	return this->asks_;
}

std::vector<Offer> &Stock::getBids()
{
	this->lockBidsQueueMutex();

	// Transfer asks
	this->bids_.insert(this->bids_.end(), this->bidsQueue_.begin(), this->bidsQueue_.end());
	this->bidsQueue_.clear();

	this->unlockBidsQueueMutex();

	return this->bids_;
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
