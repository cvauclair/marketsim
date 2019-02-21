#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <unordered_map>
#include <vector>
#include <string>

#include "offer.h"

// This Account class represents a user's currency wallet.
class Account{
	public:
		// Creates new account
		Account();

		unsigned int getId();

		// Balance methods
		void credit(float amount);
		void debit(float amount);
		float getBalance();

		// Portfolio methods
		void addShares(const std::string &symbol, unsigned int quantity);
		void removeShares(const std::string &symbol, unsigned int quantity);

		unsigned int getShares(const std::string &symbol);
		std::unordered_map<std::string, unsigned int> &getPortfolio();

		// Offers methods
		void addOffer(Offer *offer);
		float getTotalBidsValue(const std::string &symbol);
		unsigned int getTotalAsksSize(const std::string &symbol);

	private:
		static unsigned int accountCounter;

		// Account details
		std::unordered_map<std::string, unsigned int> portfolio_;

		std::unordered_map<unsigned int, Offer *> offers_;

		float balance_ = 1000.0f;

		unsigned int accountId_ = 0;
};

#endif
