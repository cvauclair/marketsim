#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include "account.h"
#include "exchange.h"

#include "stockcontroller.h"

class AccountController{
	public:
		AccountController(Exchange &exchange);

		Account &createAccount();

		// Set up actions
		void addShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);

		// Market actions
		void buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		void sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);

		// Offer actions
		std::vector<Offer *> &getOffers(unsigned int accountId, const std::string &symbol);
		void cancelOffer(unsigned int offerId);

		// Useful methods
		bool validAccounId(unsigned int accountId);

	private:
		StockController stockController_;
		Exchange *exchange_ = nullptr;
};

#endif
