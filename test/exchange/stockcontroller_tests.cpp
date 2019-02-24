#include "Catch2/catch.hpp"

#include "exchange/exchange.h"
#include "exchange/accountcontroller.h"
#include "exchange/stockcontroller.h"
#include "exchange/offercontroller.h"

// Test variables
static Exchange exchange;
static AccountController accountController(exchange);
static OfferController offerController(exchange);
static StockController stockController(exchange);
static unsigned int accountId = 0;
static unsigned int askOfferId = 0;
static unsigned int bidOfferId = 0;

// Setup exchange for testing
void setup(){
	// Clear exchange
	exchange.clear();

	// Create and setup dummy account
	accountId = accountController.createAccount();
	accountController.addShares(accountId, "AAPL", 100);
	accountController.setBalance(accountId, 1000.0f);

	// Add offers
	offerController.createAsk(accountId, "AAPL", 10, 5.0f);
	offerController.createBid(accountId, "AAPL", 16, 7.0f);
}

TEST_CASE("Add ask to stock", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Get asks of stock", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Add bid to stock", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Get bids of stock", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Set last trade price", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Get last trade price", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Get lowest ask price", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Get highest bid price", "[StockController]"){
	Exchange exchange;
	OfferController offerController(exchange);
	StockController stockController(exchange);

	// TODO
}

TEST_CASE("Set volume", "[StockController]"){
	// TODO
}

TEST_CASE("Increment volume", "[StockController]"){
	// TODO
}

TEST_CASE("Get volume", "[StockController]"){
	// TODO
}

TEST_CASE("Validate stock symbol", "[StockController]"){
	// TODO
}

TEST_CASE("Valid stock symbol", "[StockController]"){
	// TODO
}
