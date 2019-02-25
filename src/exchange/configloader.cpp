#include "configloader.h"

std::vector<std::string> ConfigLoader::loadStocks(const std::string &stocksFilename)
{
	// Init lua stuff
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	std::vector<std::string> stockSymbols = {};

	// Read data
	if(luaL_dofile(L, stocksFilename.c_str()) != 0){
		throw std::runtime_error("Error opening " + stocksFilename);
	}

	luabridge::LuaRef stocksRef = luabridge::getGlobal(L, "stocks");
	for(unsigned int i = 0; i < stocksRef.length(); ++i){
		stockSymbols.push_back(stocksRef[i+1]["symbol"].cast<std::string>());
	}

	return stockSymbols;
}

ConfigLoader::Configuration ConfigLoader::loadConfig(const std::string &configFilename)
{
	Configuration config;

	// Init lua stuff
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	luabridge::LuaRef numExchangeWorkersRef = luabridge::getGlobal(L, "num_exchange_workers");
	config.numExchangeWorkers = numExchangeWorkersRef.cast<unsigned int>();

	return config;
}
