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
	// Stop arbitrators
	for(Arbitrator &arbitrator : this->arbitrators_){
		arbitrator.stop();
	}
}

void Exchange::start()
{
	// Start arbitrators
	for(Arbitrator &arbitrator : this->arbitrators_){
		arbitrator.start();
	}
}

Account &Exchange::createAccount()
{
	Account newAccount;
	this->accounts_[newAccount.getId()] = newAccount;
	return this->accounts_[newAccount.getId()];
}

void Exchange::addShares(unsigned int accountId, const std::string &symbol, unsigned int quantity)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->accounts_[accountId].addShares(symbol, quantity);
}

void Exchange::removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->accounts_[accountId].removeShares(symbol, quantity);
}

void Exchange::buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->stocks_[symbol].addBid(quantity, price, &(this->accounts_[accountId]));
}

void Exchange::sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price)
{
	if(!this->validAccounId(accountId)){
		throw std::runtime_error("Error: Invalid account id " + std::to_string(accountId));
	}

	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	this->stocks_[symbol].addAsk(quantity, price, &(this->accounts_[accountId]));
}

bool Exchange::validAccounId(unsigned int accountId)
{
	if(this->accounts_.find(accountId) != this->accounts_.end()){
		return true;
	}
	return false;
}

Stock &Exchange::getStock(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}
	return this->stocks_[symbol];
}

float Exchange::getLastTradePrice(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	return this->stocks_[symbol].getLastTradePrice();
}

float Exchange::getHighestBid(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	return this->stocks_[symbol].getHighestBidPrice();
}

float Exchange::getLowestAsk(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	return this->stocks_[symbol].getLowestAskPrice();
}

unsigned int Exchange::getVolume(const std::string &symbol)
{
	if(!this->validStockSymbol(symbol)){
		throw std::runtime_error("Error: Invalid stock symbol " + symbol);
	}

	return this->stocks_[symbol].getVolume();
}

bool Exchange::validStockSymbol(const std::string &symbol)
{
	if(this->stocks_.find(symbol) != this->stocks_.end()){
		return true;
	}
	return false;
}
