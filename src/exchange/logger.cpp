#include "logger.h"

std::fstream Logger::logFile_ = std::fstream(logFilename, std::fstream::out);
std::mutex Logger::logMutex = std::mutex();

void Logger::log(const char *token, const char *logMsg, bool printStdout)
{
	logMutex.lock();

	if(printStdout){
		std::cout << "[" << token << "]: " << logMsg << std::endl;
	}
	logFile_ << "[" << token << "]: " << logMsg << std::endl;
	logFile_.flush();

	logMutex.unlock();
}

void Logger::log(const std::string &token, const std::string &logMsg, bool printStdout)
{
	logMutex.lock();

	if(printStdout){
		std::cout << "[" << token << "]: " << logMsg << std::endl;
	}
	logFile_ << "[" << token << "]: " << logMsg << std::endl;
	logFile_.flush();

	logMutex.unlock();
}
