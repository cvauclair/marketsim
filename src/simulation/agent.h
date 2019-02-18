#ifndef AGENT_H
#define AGENT_H

#include "exchange/tradeinterface.h"

class Agent{
	public:
		Agent(Exchange &exchange);
		~Agent();

		void doAction();

	private:
		TradeInterface *tradeInterface_ = nullptr;
		Exchange *exchange_ = nullptr;
};

#endif
