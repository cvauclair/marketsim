#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <unordered_map>
#include <string>

// This Account class represents a user's currency wallet.
class Account{
	public:
		// Creates new account
		Account();

		unsigned int getId();

		// Balance actions
		void credit(float amount);
		void debit(float amount);
		float getBalance();

		// Portfolio actions
		void addShares(const std::string &symbol, unsigned int quantity);
		void removeShares(const std::string &symbol, unsigned int quantity);

		unsigned int getShares(const std::string &symbol);
		std::unordered_map<std::string, unsigned int> &getPortfolio();


	private:
		static unsigned int accountCounter;

		std::unordered_map<std::string, unsigned int> portfolio_;
		float balance_ = 0.0f;
		unsigned int accountId_ = 0;
};

#endif
