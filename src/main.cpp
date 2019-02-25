#include <iostream>
#include <thread>
#include <chrono>

#include <QApplication>

#include "gui/mainwindow.h"

#include "exchange/accountcontroller.h"
#include "exchange/stockcontroller.h"

#include "exchange/exchangeworker.h"

#include "simulation/simulation.h"

using namespace std;

int main(int argc, char **argv)
{
	// Create exchange
	Exchange exchange;

	// Create ExchangeWorkers
	ExchangeWorker worker(exchange, {"AAPL"});
	worker.start();

	// Init controllers
	AccountController aController(exchange);
	StockController sController(exchange);

	// Run simulation
	Simulation sim(exchange, 100);

	std::this_thread::sleep_for(chrono::seconds(2));

	sim.start();

	std::this_thread::sleep_for(chrono::seconds(20));

	worker.stop();
	sim.stop();

	Logger::log("info", "AAPL price: " + std::to_string(sController.getLastTradePrice("AAPL")) + " Volume: " +
				std::to_string(sController.getVolume("AAPL")), true);

//	cout << "Max number of threads: " << std::to_string(thread::hardware_concurrency()) << endl;

//	QApplication app(argc, argv);

//	MainWindow mainWindow;
//	mainWindow.show();

//	return app.exec();

	return 0;
}
