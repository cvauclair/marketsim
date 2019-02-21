#include "agent.h"

std::random_device Agent::rd;
std::mt19937 Agent::gen(Agent::rd());
std::uniform_int_distribution<> Agent::binary(0, 1);
std::uniform_real_distribution<> Agent::percent(0.0, 1.0);
std::uniform_int_distribution<> Agent::quantity(1, 50);
std::uniform_int_distribution<> Agent::price(95, 105);

Agent::Agent(Exchange &exchange) : tradeInterface_(exchange, exchange.createAccount())
{
	this->exchange_ = &exchange;
}

Agent::~Agent()
{

}

void Agent::doAction()
{
	// Place order 0.10 percent of times
	if(Agent::percent(gen) < 0.1){
		// Decide buy/sell
		if(Agent::binary(gen) == 1){
			this->tradeInterface_.buy("AAPL", Agent::quantity(gen), Agent::price(gen));
		}else {
			this->tradeInterface_.sell("AAPL", Agent::quantity(gen), Agent::price(gen));
		}
	}
}
