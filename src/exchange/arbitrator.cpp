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
	if(this->stock_->getAsks().size() == 0 || this->stock_->getBids().size() == 0){
		return;
	}

	// Sort bids in from smallest rate to largest rate and asks from largest rate to smallest rate (we pop from the back)
	std::sort(asks.begin(), asks.end(), [](Offer &offer1, Offer &offer2){return offer1.price > offer2.price;});
	std::sort(bids.begin(), bids.end(), [](Offer &offer1, Offer &offer2){return offer1.price < offer2.price;});

	// Order matching
	while(sameRate(bids.back().price, asks.back().price)){
		this->trade(&this->stock_->getBids().back(), &this->stock_->getAsks().back());

		// Pop back if fulfilled
		if(this->stock_->getBids().back().quantity <= 0){
			this->stock_->getBids().pop_back();
		}
		if(this->stock_->getAsks().back().quantity <= 0){
			this->stock_->getAsks().pop_back();
		}
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

	Logger::log("info", this->stock_->getSymbol() + " " + std::to_string(quantityTraded) + " quantity traded", true);
}
