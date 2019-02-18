#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <unordered_map>
#include <mutex>

#include "offer.h"

class Stock{
	public:
		static Stock create(const std::string &symbol);
		Stock();
		~Stock();

		std::string &getSymbol();

		void addAsk(unsigned int quantity, float price, Account *account);
		void addBid(unsigned int quantity, float price, Account *account);

		std::vector<Offer> &getAsks();
		std::vector<Offer> &getBids();

	private:
		void setSymbol(const std::string &symbol);

		// Mutexes
		static std::unordered_map<Stock *, std::mutex> asksQueueMutexes;
		static std::unordered_map<Stock *, std::mutex> bidsQueueMutexes;

		std::string symbol_ = "";

		std::vector<Offer> asks_ = {};
		std::vector<Offer> bids_ = {};

		std::vector<Offer> asksQueue_ = {};
		std::vector<Offer> bidsQueue_ = {};
};

#endif
