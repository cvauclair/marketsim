#include "marketcontroller.h"

MarketController::MarketController(Exchange &exchange): offerController_(exchange), stockController_(exchange)
{
	this->exchange_ = &exchange;
}

std::set<Offer *, bool (*)(Offer *, Offer *)> MarketController::getAsks(const std::string &symbol)
{
	std::set<Offer *, bool (*)(Offer *, Offer *)> sortedAsks([](Offer *offer1, Offer *offer2){return offer1->price < offer2->price;});

	std::vector<unsigned int> &asks = this->stockController_.getAsks(symbol);

	this->stockController_.getStock(symbol).lockAsksQueueMutex();
	for(unsigned int offerId : asks){
		if(this->offerController_.getStatus(offerId) == Offer::PENDING | this->offerController_.getStatus(offerId) == Offer::PROCESSING){
			sortedAsks.insert(&this->offerController_.getOffer(offerId));
		}
	}
	this->stockController_.getStock(symbol).unlockAsksQueueMutex();

	return sortedAsks;
}

std::set<Offer *, bool (*)(Offer *, Offer *)> MarketController::getBids(const std::string &symbol)
{
	std::set<Offer *, bool (*)(Offer *, Offer *)> sortedBids([](Offer *offer1, Offer *offer2){return offer1->price > offer2->price;});

	std::vector<unsigned int> &bids = this->stockController_.getBids(symbol);

	this->stockController_.getStock(symbol).lockBidsQueueMutex();
	for(unsigned int offerId : bids){
		if(this->offerController_.getStatus(offerId) == Offer::PENDING | this->offerController_.getStatus(offerId) == Offer::PROCESSING){
			sortedBids.insert(&this->offerController_.getOffer(offerId));
		}
	}
	this->stockController_.getStock(symbol).unlockBidsQueueMutex();

	return sortedBids;
}

void MarketController::resolveOffers(const std::string &symbol)
{
	this->stockController_.validateStockSymbol(symbol);

	std::set<Offer *, bool (*)(Offer *, Offer *)> asks = this->getAsks(symbol);
	std::set<Offer *, bool (*)(Offer *, Offer *)> bids = this->getBids(symbol);

	if(asks.size() == 0 | bids.size() == 0){
		return;
	}

	Offer *lowestAsk = *asks.begin();
	Offer *highestBid = *bids.begin();

	this->offerController_.validateOfferId(lowestAsk->offerId);
	this->offerController_.validateOfferId(highestBid->offerId);

	while(lowestAsk->price <= highestBid->price){
		this->executeTrade(symbol, lowestAsk, highestBid);

		// Pop back if orders are fulfilled
		if(lowestAsk->quantity <= 0){
			lowestAsk->status_ = Offer::FULFILLED;
			asks.erase(lowestAsk);

			if(asks.size() == 0){
				break;
			}

			lowestAsk = *asks.begin();
		}

		if(highestBid->quantity <= 0){
			highestBid->status_ = Offer::FULFILLED;
			bids.erase(highestBid);

			if(bids.size() == 0){
				break;
			}

			highestBid = *bids.begin();
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
	ask->quantity -= quantityTraded;
	bid->quantity -= quantityTraded;

	// Update offer status
	ask->status_ = Offer::PROCESSING;
	bid->status_ = Offer::PROCESSING;

	// Update volume
	this->stockController_.incrementVolume(symbol, quantityTraded);

	// Update last trade price
	this->stockController_.setLastTradePrice(symbol, bid->price);

	Logger::log("info", symbol + " " + std::to_string(quantityTraded) + " quantity traded", true);
}
