#include "agent.h"

std::random_device Agent::rd;
std::mt19937 Agent::gen(Agent::rd());
std::uniform_int_distribution<> Agent::binary(0, 1);
std::uniform_real_distribution<> Agent::percent(0.0, 1.0);
std::uniform_int_distribution<> Agent::quantity(1, 50);
std::uniform_int_distribution<> Agent::price(10, 30);

Agent::Agent(Exchange &exchange) : aController_(exchange), sController_(exchange)
{
	this->accountId_ = this->aController_.createAccount().getId();

	// Give all accounts 100 AAPL shares
	this->aController_.addShares(this->accountId_, "AAPL", 100);
}

Agent::~Agent()
{

}

void Agent::doAction()
{
	// Place order 0.10 percent of times
	if(Agent::percent(gen) < 0.0001){
		// Decide buy/sell
		if(Agent::binary(gen) == 1){
			this->aController_.buyShares(this->accountId_, "AAPL", Agent::quantity(gen), Agent::price(gen));
		}else {
			this->aController_.sellShares(this->accountId_, "AAPL", Agent::quantity(gen), Agent::price(gen));
		}
	}
}
