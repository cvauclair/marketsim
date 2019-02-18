#include <iostream>
#include <thread>
#include <chrono>

#include <QApplication>

#include "gui/mainwindow.h"

#include "exchange/tradeinterface.h"

using namespace std;

void simulation(Exchange &exchange);

int main(int argc, char **argv)
{
	Exchange exchange;
	std::this_thread::sleep_for(chrono::seconds(2));
	simulation(exchange);
	std::this_thread::sleep_for(chrono::seconds(2));

//	cout << "Max number of threads: " << std::to_string(thread::hardware_concurrency()) << endl;

//	QApplication app(argc, argv);

//	MainWindow mainWindow;
//	mainWindow.show();

//	return app.exec();

	return 0;
}

void simulation(Exchange &exchange)
{
	TradeInterface user1(exchange, exchange.createAccount());
	user1.getAccount().credit(100000.0);
	user1.buy("AAPL", 10, 100.0);

	TradeInterface user2(exchange, exchange.createAccount());
	user2.getAccount().credit(100000.0);
	user2.getAccount().addShares("AAPL", 10);
	user2.sell("AAPL", 10, 100.0);
}
