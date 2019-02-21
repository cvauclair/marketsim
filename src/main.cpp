#include <iostream>
#include <thread>
#include <chrono>

#include <QApplication>

#include "gui/mainwindow.h"

#include "exchange/accountcontroller.h"
#include "exchange/stockcontroller.h"

#include "simulation/simulation.h"

using namespace std;

int main(int argc, char **argv)
{
	// Create exchange
	Exchange exchange;

	// Init controllers
	AccountController aController(exchange);
	StockController sController(exchange);

	Simulation sim(exchange, 50);
	exchange.start();
	std::this_thread::sleep_for(chrono::seconds(2));
	sim.start();
	std::this_thread::sleep_for(chrono::seconds(10));
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
