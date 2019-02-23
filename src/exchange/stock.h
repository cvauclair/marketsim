#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <unordered_map>
#include <mutex>
#include <list>

#include "offer.h"

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

		void addAsk(unsigned int offerId);
		void addBid(unsigned int offerId);

		std::vector<unsigned int> &getAsks();
		std::vector<unsigned int> &getBids();

		void setLastTradePrice(float lastTradePrice);
		float getLastTradePrice();

		float getLowestAskPrice();
		float getHighestBidPrice();

		void setVolume(unsigned int volume);
		unsigned int getVolume();

	private:
		// Mutexes
		static std::unordered_map<Stock *, std::mutex> asksQueueMutexes;
		static std::unordered_map<Stock *, std::mutex> bidsQueueMutexes;

		std::string symbol_ = "";

		float lastTradePrice_ = 0.0f;
		float lowestAskPrice_ = 0.0f;
		float highestBidPrice_ = 0.0f;

		unsigned int volume_ = 0;

		// Vector of asks/bids (their ids)
		std::vector<unsigned int> asks_ = {};
		std::vector<unsigned int> bids_ = {};
};

#endif
