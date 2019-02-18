#include <iostream>
#include <thread>

#include <QApplication>

#include "gui/mainwindow.h"

using namespace std;

int main(int argc, char **argv)
{
	cout << "Max number of threads: " << std::to_string(thread::hardware_concurrency()) << endl;

//	QApplication app(argc, argv);

//	MainWindow mainWindow;
//	mainWindow.show();

//	return app.exec();
	return 0;
}
