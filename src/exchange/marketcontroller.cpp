#include "marketcontroller.h"

MarketController::MarketController(Exchange &exchange):
	accountController_(exchange),
	offerController_(exchange),
	stockController_(exchange)
{
	this->exchange_ = &exchange;
}

std::vector<unsigned int> MarketController::getSortedAsks(const std::string &symbol)
{
	std::vector<unsigned int> sortedAsks;
	std::vector<unsigned int> asks = this->stockController_.getAsks(symbol);

	for(unsigned int offerId: asks){
		if(this->offerController_.getStatus(offerId) == Offer::PENDING | this->offerController_.getStatus(offerId) == Offer::PROCESSING){
			sortedAsks.push_back(offerId);
		}
	}

	this->sortAscendingOrder(sortedAsks);

	return sortedAsks;
}

std::vector<unsigned int> MarketController::getSortedBids(const std::string &symbol)
{
	std::vector<unsigned int> sortedBids;
	std::vector<unsigned int> bids = this->stockController_.getBids(symbol);

	for(unsigned int offerId : bids){
		if(this->offerController_.getStatus(offerId) == Offer::PENDING | this->offerController_.getStatus(offerId) == Offer::PROCESSING){
			sortedBids.push_back(offerId);
		}
	}

	this->sortAscendingOrder(sortedBids);

	return sortedBids;
}

void MarketController::sortAscendingOrder(std::vector<unsigned int> &offerIds)
{
	// Locking all of the exchange's mutexes fixes a crash where one of the offer ids was set to 0 mid sorting
	this->exchange_->lockAccountsMutex();
	this->exchange_->lockStocksMutex();

	std::sort(offerIds.begin(), offerIds.end(), [this](const unsigned int &offerId1, const unsigned int &offerId2){
		return this->offerController_.comparePrice(offerId1, offerId2);
	});

	this->exchange_->unlockAccountsMutex();
	this->exchange_->unlockStocksMutex();
}

void MarketController::sortDescendingOrder(std::vector<unsigned int> &offerIds)
{
	// Locking all of the exchange's mutexes fixes a crash where one of the offer ids was set to 0 mid sorting
	this->exchange_->lockAccountsMutex();
	this->exchange_->lockStocksMutex();

	std::sort(offerIds.begin(), offerIds.end(), [this](const unsigned int &offerId1, const unsigned int &offerId2){
		return !this->offerController_.comparePrice(offerId1, offerId2);
	});

	this->exchange_->unlockAccountsMutex();
	this->exchange_->unlockStocksMutex();
}

void MarketController::resolveOffers(const std::string &symbol)
{
	this->stockController_.validateStockSymbol(symbol);

	std::vector<unsigned int> sortedAsks = this->getSortedAsks(symbol);
	std::vector<unsigned int> sortedBids = this->getSortedBids(symbol);

	unsigned int lowestAskId = 0;
	unsigned int highestBidId = 0;

	while(sortedAsks.size() != 0 & sortedBids.size() != 0){
		lowestAskId = sortedAsks.back();
		highestBidId = sortedBids.back();

		// Break if lowest ask is higher than highest bid, in which case no trading can occur
		if(this->offerController_.getPrice(lowestAskId) > this->offerController_.getPrice(highestBidId)){
			break;
		}

		this->executeTrade(symbol, lowestAskId, highestBidId);

		// Pop back if orders are fulfilled
		if(this->offerController_.getQuantity(lowestAskId) <= 0){
			this->offerController_.setStatus(lowestAskId, Offer::FULFILLED);
			sortedAsks.pop_back();
		}

		if(this->offerController_.getQuantity(highestBidId) <= 0){
			this->offerController_.setStatus(highestBidId, Offer::FULFILLED);
			sortedBids.pop_back();
		}
	}
}

void MarketController::executeTrade(const std::string &symbol, unsigned int askId, unsigned int bidId)
{
	// Get quantity that will be traded
	unsigned int quantityTraded = std::min(this->offerController_.getQuantity(askId), this->offerController_.getQuantity(bidId));

	float askPrice = this->offerController_.getPrice(askId);
	float bidPrice = this->offerController_.getPrice(bidId);

	// Adjust buyer account
	unsigned int buyerAccountId = this->offerController_.getAccountId(bidId);
	this->accountController_.addShares(buyerAccountId , symbol, quantityTraded);
	this->accountController_.debit(buyerAccountId, quantityTraded * bidPrice);

	// Adjust seller account
	unsigned int sellerAccountId = this->offerController_.getAccountId(askId);
	this->accountController_.removeShares(sellerAccountId, symbol, quantityTraded);
	this->accountController_.credit(sellerAccountId, quantityTraded * askPrice);

	// Check if arbitration required
	if(askPrice < bidPrice){
		float arbitrationProfit = quantityTraded * (bidPrice - askPrice);
		this->exchange_->exchangeAccount_->credit(arbitrationProfit);
		Logger::log("info", "Arbitration profit: " + std::to_string(arbitrationProfit), true);
	}

	// Adjust offers
	this->offerController_.decrementQuantity(askId, quantityTraded);
	this->offerController_.decrementQuantity(bidId, quantityTraded);

	// Update offer status
	this->offerController_.setStatus(askId, Offer::PROCESSING);
	this->offerController_.setStatus(bidId, Offer::PROCESSING);

	// Update volume
	this->stockController_.incrementVolume(symbol, quantityTraded);

	// Update last trade price
	this->stockController_.setLastTradePrice(symbol, bidPrice);

	Logger::log("info", symbol + " " + std::to_string(quantityTraded) + " quantity traded @ " + std::to_string(bidPrice), true);
}
