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
		void setBalance(float balance);
		float getBalance();
		void credit(float amount);
		void debit(float amount);

		// Portfolio methods
		void addShares(const std::string &symbol, unsigned int quantity);
		void removeShares(const std::string &symbol, unsigned int quantity);

		unsigned int getShares(const std::string &symbol);
		std::unordered_map<std::string, unsigned int> &getPortfolio();

		// Offers methods
		void addOffer(unsigned int offerId);
		std::vector<unsigned int> &getPendingOffersId();

	private:
		static unsigned int accountCounter;

		// Account details
		std::unordered_map<std::string, unsigned int> portfolio_;

		std::vector<unsigned int> pendingOffersIds_;

		float balance_ = 1000.0f;

		unsigned int accountId_ = 0;
};

#endif
