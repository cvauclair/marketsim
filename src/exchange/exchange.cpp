#include "exchange.h"

Exchange::Exchange()
{
	// Create exchange account
	this->exchangeAccount_ = new Account();

	// Load data
	for(const std::string &symbol : SYMBOLS){
		// Create stocks
		this->stocks_[symbol] = Stock::create(symbol);

		// Create arbitrators
		this->arbitrators_.emplace_back(&(this->stocks_[symbol]), this->exchangeAccount_);

		Logger::log("debug", "Stock " + symbol + " added", true);
	}
}

Exchange::~Exchange()
{
	// Stop arbitrators
	for(Arbitrator &arbitrator : this->arbitrators_){
		arbitrator.stop();
	}

	// Delete exchange account
	delete this->exchangeAccount_;
}

void Exchange::start()
{
	// Start arbitrators
	for(Arbitrator &arbitrator : this->arbitrators_){
		arbitrator.start();
	}
}
