#ifndef EXCHANGEWORKER_H
#define EXCHANGEWORKER_H

#include <thread>

#include "marketcontroller.h"

class Exchange;
class ExchangeWorker{
	public:
		ExchangeWorker(Exchange &exchange, const std::vector<std::string> &stockSymbols);

		void start();
		void run();
		void stop();

	private:
		MarketController marketController_;
		std::vector<std::string> stockSymbols_;

		std::thread *thread_ = nullptr;
		bool stop_ = false;
};

#endif
