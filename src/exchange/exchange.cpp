#include "exchange.h"

Exchange::Exchange()
{
	// Load data
	for(const std::string &symbol : SYMBOLS){
		// Create stocks
		this->stocks_[symbol] = Stock::create(symbol);

		// Create arbitrators
		this->arbitrators_.emplace_back(&(this->stocks_[symbol]));

		Logger::log("debug", "Stock " + symbol + " added", true);
	}
}

Exchange::~Exchange()
{

}

Account &Exchange::createAccount()
{
	Account newAccount;
	this->accounts_[newAccount.getId()] = newAccount;
	return this->accounts_[newAccount.getId()];
}

Stock &Exchange::getStock(const std::string &symbol)
{
	if(this->stocks_.find(symbol) != this->stocks_.end()){
		return this->stocks_[symbol];
	}else{
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}
}
