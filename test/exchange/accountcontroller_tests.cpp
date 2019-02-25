#include "Catch2/catch.hpp"

#include "exchange/exchange.h"
#include "exchange/accountcontroller.h"

TEST_CASE("Create new account", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int newAccountId =  0;

	REQUIRE_NOTHROW(newAccountId = accountController.createAccount());
	REQUIRE(newAccountId == 1);
	REQUIRE_NOTHROW(accountController.validateAccountId(newAccountId));
}

TEST_CASE("Setting account number of shares", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getShares(accountId, "AAPL") == 0);
	REQUIRE_NOTHROW(accountController.setShares(accountId, "AAPL", 10));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 10);
}

TEST_CASE("Adding shares to account", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getShares(accountId, "AAPL") == 0);
	REQUIRE_NOTHROW(accountController.addShares(accountId, "AAPL", 10));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 10);
	REQUIRE_NOTHROW(accountController.addShares(accountId, "AAPL", 10));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 20);
}

TEST_CASE("Remove shares to account", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getShares(accountId, "AAPL") == 0);
	REQUIRE_NOTHROW(accountController.setShares(accountId, "AAPL", 10));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 10);
	REQUIRE_NOTHROW(accountController.removeShares(accountId, "AAPL", 5));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 5);
}

TEST_CASE("Set account balance valid amount", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_NOTHROW(accountController.setBalance(accountId, 178.2f));
	REQUIRE(accountController.getBalance(accountId) == 178.2f);
}

TEST_CASE("Set account balance invalid amount", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_THROWS_WITH(accountController.setBalance(accountId, -10.0), "Error: Negative balance value");
}

TEST_CASE("Credit account valid amount", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_NOTHROW(accountController.credit(accountId, 10.0f));
	REQUIRE(accountController.getBalance(accountId) == 10.0f);
}

TEST_CASE("Credit account invalid amount", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_THROWS_WITH(accountController.credit(accountId, -10.0), "Error: Negative credit amount");
}

TEST_CASE("Debit account valid amount", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_NOTHROW(accountController.credit(accountId, 10.0f));
	REQUIRE(accountController.getBalance(accountId) == 10.0f);
	REQUIRE_NOTHROW(accountController.debit(accountId, 6.0f));
	REQUIRE(accountController.getBalance(accountId) == 4.0f);
}

TEST_CASE("Debit account invalid amount", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_THROWS_WITH(accountController.debit(accountId, -10.0), "Error: Negative debit amount");
}

TEST_CASE("Debit account insufficient funds", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_THROWS_WITH(accountController.debit(accountId, 10.0f), "Error: Insufficient funds");
}

TEST_CASE("Buy shares sufficient funds", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	Offer desiredOffer(Offer::BID, "AAPL", 5, 10.0f, accountId);

	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_NOTHROW(accountController.credit(accountId, 100.0f));
	REQUIRE(accountController.getBalance(accountId) == 100.0f);

	REQUIRE_NOTHROW(accountController.buyShares(accountId, "AAPL", 5, 10.0f));

	REQUIRE(accountController.getPendingOffers(accountId, "AAPL").size() == 1);
	REQUIRE(accountController.getTotalBidsValue(accountId, "AAPL") == 50.0f);
	REQUIRE(accountController.getTotalAsksSize(accountId, "AAPL") == 0);

	// TODO: Compare with desired offer
}

TEST_CASE("Buy shares insufficient funds", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getBalance(accountId) == 0.0f);
	REQUIRE_NOTHROW(accountController.credit(accountId, 100.0f));
	REQUIRE(accountController.getBalance(accountId) == 100.0f);

	REQUIRE_THROWS_WITH(accountController.buyShares(accountId, "AAPL", 5, 100.0f), "Error: Insufficient funds account " + std::to_string(accountId));

	REQUIRE(accountController.getPendingOffers(accountId, "AAPL").size() == 0);
	REQUIRE(accountController.getTotalBidsValue(accountId, "AAPL") == 0.0f);
	REQUIRE(accountController.getTotalAsksSize(accountId, "AAPL") == 0);
}

TEST_CASE("Sell shares sufficient shares", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	Offer desiredOffer(Offer::BID, "AAPL", 5, 10.0f, accountId);

	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getShares(accountId, "AAPL") == 0);
	REQUIRE_NOTHROW(accountController.addShares(accountId, "AAPL", 100));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 100);

	REQUIRE_NOTHROW(accountController.sellShares(accountId, "AAPL", 5, 10.0f));

	REQUIRE(accountController.getPendingOffers(accountId, "AAPL").size() == 1);
	REQUIRE(accountController.getTotalBidsValue(accountId, "AAPL") == 0.0f);
	REQUIRE(accountController.getTotalAsksSize(accountId, "AAPL") == 5);

	// TODO: Compare with desired offer
}

TEST_CASE("Buy shares insufficient shares", "[AccountController]"){
	Exchange exchange;
	AccountController accountController(exchange);

	unsigned int accountId =  0;
	REQUIRE_NOTHROW(accountId = accountController.createAccount());

	REQUIRE(accountController.getShares(accountId, "AAPL") == 0);
	REQUIRE_NOTHROW(accountController.addShares(accountId, "AAPL", 100));
	REQUIRE(accountController.getShares(accountId, "AAPL") == 100);

	REQUIRE_THROWS_WITH(accountController.sellShares(accountId, "AAPL", 500, 10.0f), "Error: Insufficient AAPL shares account " + std::to_string(accountId));

	REQUIRE(accountController.getPendingOffers(accountId, "AAPL").size() == 0);
	REQUIRE(accountController.getTotalBidsValue(accountId, "AAPL") == 0.0f);
	REQUIRE(accountController.getTotalAsksSize(accountId, "AAPL") == 0);
}
