#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

static const std::string logFilename = "log.txt";

// Logging singleton class that writes log messages in a logfile and optionally
// prints them to stdout. Log messages must have an associated token.
class Logger{
	public:
		static void log(const char *token, const char *logMsg, bool printStdout = false);
		static void log(const std::string &token, const std::string &logMsg, bool printStdout = false);

	private:
		static std::fstream logFile_;
		static std::mutex logMutex;
};

#endif
