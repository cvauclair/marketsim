#include "arbitrator.h"

Arbitrator::Arbitrator(Stock *stock)
{
	this->stock_ = stock;
}

Arbitrator::~Arbitrator()
{
	delete this->t;
}

void Arbitrator::start()
{
	this->t = new std::thread(&Arbitrator::run, this);
}

void Arbitrator::stop()
{
	this->stop_ = true;
	this->t->join();
	Logger::log("debug", this->stock_->getSymbol() + " arbitrator stopped", true);
}

void Arbitrator::run()
{
	Logger::log("debug", this->stock_->getSymbol() + " arbitrator started", true);
	while(!this->stop_){
		this->resolveOffers();
	}
}

void Arbitrator::resolveOffers()
{
	std::vector<Offer> &asks = this->stock_->getAsks();
	std::vector<Offer> &bids = this->stock_->getBids();

	// Check if there are traded to make
	if(asks.size() == 0 || bids.size() == 0){
		return;
	}

	// Sort bids in from smallest rate to largest rate and asks from largest rate to smallest rate (we pop from the back)
	std::sort(asks.begin(), asks.end(), [](Offer &offer1, Offer &offer2){return offer1.price > offer2.price;});
	std::sort(bids.begin(), bids.end(), [](Offer &offer1, Offer &offer2){return offer1.price < offer2.price;});

	// Order matching
	while(sameRate(bids.back().price, asks.back().price)){
		this->trade(&bids.back(), &asks.back());

		// Pop back if fulfilled
		if(bids.back().quantity <= 0){
			bids.pop_back();
		}
		if(asks.back().quantity <= 0){
			asks.pop_back();
		}

		if(asks.size() == 0 || bids.size() == 0){
			break;
		}
	}

	// Set highest bid/lowest ask after matching has been executed
	// (if there are any asks/bids)
	if(asks.size() != 0){
		this->stock_->lowestAskPrice_ = asks.back().price;
	}
	if(bids.size() != 0){
		this->stock_->highestBidPrice_ = bids.back().price;
	}
}

void Arbitrator::trade(Offer *bid, Offer *ask)
{
	// Check if rates are the same
	if(!sameRate(bid->price, ask->price)){
		throw std::runtime_error("Error: Rate mismatch");
	}

	// Get quantity that will be traded
	unsigned int quantityTraded = std::min(bid->quantity, ask->quantity);

	// Adjust buyer account
	bid->account->addShares(this->stock_->getSymbol(), quantityTraded);
	bid->account->debit(quantityTraded * bid->price);

	// Adjust seller account
	ask->account->removeShares(this->stock_->getSymbol(), quantityTraded);
	ask->account->credit(quantityTraded * bid->price);

	// Adjust offers
	bid->quantity -= quantityTraded;
	ask->quantity -= quantityTraded;

	// Update volume
	this->stock_->volume_ += quantityTraded;

	// Update last trade price
	this->stock_->lastTradePrice_ = bid->price;

	Logger::log("info", this->stock_->getSymbol() + " " + std::to_string(quantityTraded) + " quantity traded", true);
}
