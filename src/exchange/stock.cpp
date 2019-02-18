#include "stock.h"

Stock::Stock()
{
	// Create mutexes
	Stock::asksQueueMutexes[this];
	Stock::bidsQueueMutexes[this];
}

Stock Stock::create(const std::string &symbol)
{
	Stock newStock;
	newStock.setSymbol(symbol);
	return newStock;
}

std::string &Stock::getSymbol()
{
	return this->symbol_;
}

void Stock::addAsk(unsigned int quantity, float price, Account *account)
{
	this->asksQueue_.emplace_back(quantity, price, account);
}

void Stock::addBid(unsigned int quantity, float price, Account *account)
{
	this->bidsQueue_.emplace_back(quantity, price, account);
}

std::vector<Offer> &Stock::getAsks()
{
	Stock::asksQueueMutexes[this].lock();

	// Transfer asks
	this->asks_.insert(this->asks_.end(), this->asksQueue_.begin(), this->asksQueue_.end());
	this->asksQueue_.clear();

	Stock::asksQueueMutexes[this].unlock();
}

std::vector<Offer> &Stock::getBids()
{
	Stock::bidsQueueMutexes[this].lock();

	// Transfer asks
	this->bids_.insert(this->bids_.end(), this->bidsQueue_.begin(), this->bidsQueue_.end());
	this->bidsQueue_.clear();

	Stock::bidsQueueMutexes[this].unlock();
}
