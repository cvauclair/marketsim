#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <unordered_map>
#include <mutex>

#include "offer.h"
#include "logger.h"

class Arbitrator;
class Stock{
	friend class Arbitrator;
	public:
	    static Stock create(const std::string &symbol);
		Stock();

		void lockAsksQueueMutex();
		void unlockAsksQueueMutex();
		void lockBidsQueueMutex();
		void unlockBidsQueueMutex();

		std::string &getSymbol();

		void addAsk(unsigned int quantity, float price, Account *account);
		void addBid(unsigned int quantity, float price, Account *account);

		std::vector<Offer> &getAsks();
		std::vector<Offer> &getBids();

		float getLastTradePrice();
		float getLowestAskPrice();
		float getHighestBidPrice();

	private:
		// Mutexes
		static std::unordered_map<Stock *, std::mutex> asksQueueMutexes;
		static std::unordered_map<Stock *, std::mutex> bidsQueueMutexes;

		std::string symbol_ = "";

		float lastTradePrice_ = 0.0f;
		float lowestAskPrice_ = 0.0f;
		float highestBidPrice_ = 0.0f;

		std::vector<Offer> asks_ = {};
		std::vector<Offer> bids_ = {};

		std::vector<Offer> asksQueue_ = {};
		std::vector<Offer> bidsQueue_ = {};
};

#endif
