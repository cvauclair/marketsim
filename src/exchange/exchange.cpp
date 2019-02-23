#include "exchange.h"

std::mutex Exchange::accountsMutex_;
std::mutex Exchange::offersMutex_;
std::mutex Exchange::stocksMutex_;

Exchange::Exchange()
{
	// Create exchange account
	this->exchangeAccount_ = new Account();

	// Load data
	for(const std::string &symbol : SYMBOLS){
		// Create stocks
		this->stocks_[symbol] = Stock::create(symbol);

		Logger::log("debug", "Stock " + symbol + " added", true);
	}
}

Exchange::~Exchange()
{
	// Delete exchange account
	delete this->exchangeAccount_;
}

void Exchange::lockAccountsMutex()
{
	while(!this->accountsMutex_.try_lock()){}
}

void Exchange::unlockAccountsMutex()
{
	this->accountsMutex_.unlock();
}

void Exchange::lockStocksMutex()
{
	while(!this->stocksMutex_.try_lock()){}
}

void Exchange::unlockStocksMutex()
{
	this->stocksMutex_.unlock();
}

void Exchange::lockOffersMutex()
{
	while(!this->offersMutex_.try_lock()){}
}

void Exchange::unlockOffersMutex()
{
	this->offersMutex_.unlock();
}
