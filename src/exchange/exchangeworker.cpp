#include "exchangeworker.h"

ExchangeWorker::ExchangeWorker(Exchange &exchange, std::vector<std::string> &stockSymbols): marketController_(exchange)
{
	this->stockSymbols_ = stockSymbols;
}

void ExchangeWorker::start()
{
	this->thread_ = new std::thread(&ExchangeWorker::run, this);
}

void ExchangeWorker::run()
{
	while(!this->stop_){
		for(const std::string &stockSymbol : this->stockSymbols_){
			this->marketController_.resolveOffers(stockSymbol);
		}
	}
}

void ExchangeWorker::stop()
{
	this->stop_ = true;
}
