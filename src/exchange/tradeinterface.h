#ifndef TRADEINTERFACE_H
#define TRADEINTERFACE_H

#include "exchange.h"

// This class represents the interface an account holder would have with the exchange
class TradeInterface{
	public:
		TradeInterface(Exchange &exchange, Account &account);

		// Market actions
		void buy(const std::string &symbol, unsigned int quantity, float price);
		void sell(const std::string &symbol, unsigned int quantity, float price);

		Account &getAccount();

	private:
		Exchange *exchange_ = nullptr;
		Account *account_ = nullptr;
};

#endif
