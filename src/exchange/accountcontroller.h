#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include "account.h"
#include "exchange.h"

#include "offercontroller.h"
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
		float getTotalBidsValue(unsigned int accountId, const std::string &symbol);
		unsigned int getTotalAsksSize(unsigned int accountId, const std::string &symbol);
		std::vector<unsigned int> getPendingOffers(unsigned int accountId, const std::string &symbol);
		void cancelOffer(unsigned int offerId);

		// This methods will throw an exception if the account id is invalid
		// and will do nothing otherwise
		void validateAccountId(unsigned int accountId);

		// This method returns true if the account id is valid and false if it is invalid.
		// A valid account id means that it is in the hashtable of the exchange.
		bool validAccounId(unsigned int accountId);

	private:
		OfferController offerController_;
		StockController stockController_;
		Exchange *exchange_ = nullptr;
};

#endif
