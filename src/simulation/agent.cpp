#include "agent.h"

std::random_device Agent::rd;
std::mt19937 Agent::gen(Agent::rd());
std::uniform_real_distribution<> Agent::random(0.0, 1.0);

Agent::Agent(Exchange &exchange) : aController_(exchange), oController_(exchange), sController_(exchange)
{
	this->accountId_ = this->aController_.createAccount();

	// Give all accounts 100 AAPL shares
	this->aController_.addShares(this->accountId_, "AAPL", 100);
}

Agent::~Agent()
{

}

void Agent::doAction()
{
	// Basic agent strategy:
	//	if first offer then
	//		random offer generated
	//	else
	//		if last offer pending then
	//			33% chance nothing
	//			33% chance cancel and raise/lower price (depending on whether bid/ask)
	//				50% chance use CURRENT price
	//				50% chance use adjust price
	//			33% chance change strategy (from buyer to seller or vice-versa)

	// Get data
	std::vector<unsigned int> offerIds = this->aController_.getPendingOffers(this->accountId_, "AAPL");
	unsigned int shareQuantity = this->aController_.getShares(this->accountId_, "AAPL");
	float balance = this->aController_.getBalance(this->accountId_);

	if(offerIds.size() == 0){
		// Random offer
		if(Agent::random(gen) > 0.5){
			// Sell between 10 and 30 shares or between 10 and 50 $/share
			this->aController_.sellShares(this->accountId_, "AAPL", 20 * Agent::random(gen) + 10, 40 * Agent::random(gen) + 10);
		}else {
			// Buy between 10 and 30 shares or between 10 and 50 $/share
			this->aController_.buyShares(this->accountId_, "AAPL", 20 * Agent::random(gen) + 10, 40 * Agent::random(gen) + 10);
		}
	}else{
		Offer offer = this->oController_.getOfferCopy(offerIds[0]);
		float randomChoice = Agent::random(gen);

		if(randomChoice < 0.33){
			// Nothing
		}else if(randomChoice > 0.33 & randomChoice < 0.66){
			// Cancel and change price
			this->aController_.cancelOffer(offerIds[0]);

			// Change offer
			if(offer.type_ == Offer::ASK){
				// Sell again at lower price
				if(Agent::random(gen) < 0.5){
					this->aController_.sellShares(this->accountId_, "AAPL", offer.quantity, CURRENT);
				}else{
					this->aController_.sellShares(this->accountId_, "AAPL", offer.quantity, offer.price * (1.0 - Agent::random(gen)));
				}
			}else{
				// Buy again at higher price
				if(Agent::random(gen) < 0.5){
					this->aController_.buyShares(this->accountId_, "AAPL", offer.quantity, CURRENT);
				}else{
					this->aController_.buyShares(this->accountId_, "AAPL", offer.quantity, offer.price * (1.0 + Agent::random(gen)));
				}
			}
		}else{
			// Change strategy
			if(offer.type_ == Offer::ASK){
				// Sell between 10 and 30 shares or between 10 and 50 $/share
				this->aController_.buyShares(this->accountId_, "AAPL", 20 * Agent::random(gen) + 10, 40 * Agent::random(gen) + 10);
			}else {
				// Buy between 10 and 30 shares or between 10 and 50 $/share
				this->aController_.sellShares(this->accountId_, "AAPL", 20 * Agent::random(gen) + 10, 40 * Agent::random(gen) + 10);
			}
		}
	}
}

float Agent::getTotalOfferMoneySize(const std::string &symbol)
{

}

unsigned int Agent::getTotalOfferShareSize(const std::string &symbol)
{

}
