#ifndef ARBITRATOR_H
#define ARBITRATOR_H

#include <algorithm>
#include <thread>

#include "stock.h"

#include "logger.h"
#include "utility.h"

// The Arbitrator class is associated with a CurrencyPair and takes care
// of matching buyers and sellers.
class Arbitrator{
	public:
		Arbitrator(Stock *stock);
		~Arbitrator();

		void start();
		void stop();

		void resolveOffers();

	protected:
		void run();
		void trade(Offer *bid, Offer *ask);

	private:
		Stock *stock_ = nullptr;

		std::thread *t = nullptr;
		bool stop_ = false;
};

#endif
