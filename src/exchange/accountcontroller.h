#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include "account.h"
#include "exchange.h"

#include "stockcontroller.h"

class AccountController{
	public:
		AccountController(Exchange &exchange);

		// Account methods
		Account &createAccount();
		void addShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void removeShares(unsigned int accountId, const std::string &symbol, unsigned int quantity);
		void buyShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		void sellShares(unsigned int accountId, const std::string &symbol, unsigned int quantity, float price = CURRENT);
		bool validAccounId(unsigned int accountId);

	private:
		StockController stockController_;
		Exchange *exchange_ = nullptr;
};

#endif
