#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <unordered_map>
#include <mutex>
#include <list>

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
		void addAsk(Offer &offer);

		void addBid(unsigned int quantity, float price, Account *account);
		void addBid(Offer &offer);

		std::vector<Offer> &getAsks();
		std::vector<Offer> &getBids();

		float getLastTradePrice();
		float getLowestAskPrice();
		float getHighestBidPrice();
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

		std::vector<Offer> asks_ = {};
		std::vector<Offer> bids_ = {};

		std::vector<Offer> asksQueue_ = {};
		std::vector<Offer> bidsQueue_ = {};
};

#endif
