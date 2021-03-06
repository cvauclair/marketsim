#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <thread>

#include "exchange/exchange.h"
#include "exchange/accountcontroller.h"
#include "exchange/stockcontroller.h"

#include "exchange/logger.h"

#include "agent.h"

class Simulation{
	public:
		Simulation(Exchange &exchange, unsigned int numAgents);
		~Simulation();

		void start();
		void run();
		void stop();

	private:
		AccountController aController_;
		StockController sController_;

		std::vector<Agent> agents_ = {};

		std::thread *t = nullptr;
		bool stop_ = false;
};

#endif
