#include "marketcontroller.h"

MarketController::MarketController(Exchange &exchange): stockController_(exchange)
{
	this->exchange_ = &exchange;
}

std::set<Offer *, bool(*)(Offer *, Offer *)> MarketController::getAsks(const std::string &symbol)
{
	std::set<Offer *, bool(*)(Offer *, Offer *)> sortedAsks([](Offer *offer1, Offer *offer2){return offer1->price < offer2->price;});
	std::vector<Offer> &asks = this->stockController_.getAsks(symbol);

	for(auto it = asks.begin(); it != asks.end(); ++it){
		if(it->status_ == Offer::PENDING | it->status_ == Offer::PROCESSING){
			sortedAsks.insert(&(*it));
		}
	}

	return sortedAsks;
}

std::set<Offer *, bool(*)(Offer *, Offer *)> MarketController::getBids(const std::string &symbol)
{
	std::set<Offer *, bool(*)(Offer *, Offer *)> sortedBids([](Offer *offer1, Offer *offer2){return offer1->price < offer2->price;});
	std::vector<Offer> &bids = this->stockController_.getBids(symbol);

	for(auto it = bids.begin(); it != bids.end(); ++it){
		if(it->status_ == Offer::PENDING | it->status_ == Offer::PROCESSING){
			sortedBids.insert(&(*it));
		}
	}

	return sortedBids;
}

void MarketController::resolveOffers(const std::string &symbol)
{
	this->stockController_.validateStockSymbol(symbol);

	auto asks = this->getAsks(symbol);
	auto bids = this->getBids(symbol);

	if(asks.size() == 0 | bids.size() == 0){
		return;
	}

	for(auto askIt = asks.begin(); askIt != asks.end(); ++askIt){
		for(auto bidIt = bids.rbegin(); bidIt != bids.rend(); ++bidIt){
			if((*askIt)->price <= (*bidIt)->price){
				this->executeTrade(symbol, (*askIt), (*bidIt));
			}else{
				// If prices do not allow for a trade, return
				return;
			}
		}
	}
}

void MarketController::executeTrade(const std::string &symbol, Offer *ask, Offer *bid)
{
	// Get quantity that will be traded
	unsigned int quantityTraded = std::min(bid->quantity, ask->quantity);

	// Adjust buyer account
	bid->account->addShares(symbol, quantityTraded);
	bid->account->debit(quantityTraded * bid->price);

	// Adjust seller account
	ask->account->removeShares(symbol, quantityTraded);
	ask->account->credit(quantityTraded * ask->price);

	// Check if arbitration required
	float arbitrationProfit = quantityTraded * (bid->price - ask->price);
	if(bid->price < ask->price){
		this->exchange_->exchangeAccount_->credit(arbitrationProfit);
		Logger::log("info", "Arbitration profit: " + std::to_string(arbitrationProfit), true);
	}

	// Adjust offers
	bid->quantity -= quantityTraded;
	ask->quantity -= quantityTraded;

	// Update volume
	this->stockController_.incrementVolume(symbol, quantityTraded);

	// Update last trade price
	this->stockController_.setLastTradePrice(symbol, bid->price);

	Logger::log("info", symbol + " " + std::to_string(quantityTraded) + " quantity traded", true);
}
