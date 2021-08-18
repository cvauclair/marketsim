#include "Catch2/catch.hpp"

#include "exchange/exchange.h"
#include "exchange/controllers.h"

TEST_CASE("Sort ask offers", "[MarketController]"){
	Exchange exchange;
	AccountController accountController(exchange);
	MarketController marketController(exchange);
	OfferController offerController(exchange);
	StockController stockController(exchange);

	unsigned int accountId = accountController.createAccount();
	accountController.addShares(accountId, "AAPL", 1000000);
	accountController.setBalance(accountId, 1000000);

	std::vector<unsigned int> offerIds;
	for(unsigned int i = 0; i < 1000; i++){
		offerIds.push_back(offerController.createAsk(accountId, "AAPL", 1, i));
	}

	std::vector<unsigned int> desiredOfferIds = offerIds;
	std::random_shuffle(offerIds.begin(), offerIds.end());

	marketController.sortAscendingOrder(offerIds);

	REQUIRE(offerIds == desiredOfferIds);

	REQUIRE(marketController.getSortedAsks("AAPL") == desiredOfferIds);
}
