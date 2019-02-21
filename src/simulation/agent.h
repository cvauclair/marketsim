#ifndef AGENT_H
#define AGENT_H

#include <random>

#include "exchange/tradeinterface.h"

class Agent{
	public:
		Agent(Exchange &exchange);
		~Agent();

		void doAction();

	private:
		// Random number generators
		static std::random_device rd;	//Will be used to obtain a seed for the random number engine
		static std::mt19937 gen;				//Standard mersenne_twister_engine seeded with rd()
		static std::uniform_int_distribution<> binary;
		static std::uniform_real_distribution<> percent;
		static std::uniform_int_distribution<> quantity;
		static std::uniform_int_distribution<> price;

		TradeInterface tradeInterface_;
};

#endif
