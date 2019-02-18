#include "agent.h"

Agent::Agent(Exchange &exchange)
{
	this->tradeInterface_ = new TradeInterface(exchange, exchange.createAccount());
	this->exchange_ = &exchange;
}

Agent::~Agent()
{
	delete this->tradeInterface_;
}

void Agent::doAction()
{

}
