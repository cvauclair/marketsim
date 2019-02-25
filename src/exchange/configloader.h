#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <vector>
#include <string>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

class ConfigLoader{
	public:
		struct Configuration{
			unsigned int numExchangeWorkers = 0;
		};

		static std::vector<std::string> loadStocks(const std::string &stocksFilename);
		static Configuration loadConfig(const std::string &configFilename);
};

#endif
