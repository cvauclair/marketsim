cmake_minimum_required(VERSION 3.10)

project(marketsim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Find threading library
find_package(Threads)

# Find lua library
find_package(Lua REQUIRED)
set(LUA_LIBRARIES "/usr/lib/liblua5.3.so")

include_directories(src test deps ${LUA_INCLUDE_DIR})

set(exchangeSRCS
	"src/exchange/account.cpp"
	"src/exchange/accountcontroller.cpp"
	"src/exchange/configloader.cpp"
	"src/exchange/exchange.cpp"
	"src/exchange/exchangeworker.cpp"
	"src/exchange/logger.cpp"
	"src/exchange/marketcontroller.cpp"
	"src/exchange/offer.cpp"
	"src/exchange/offercontroller.cpp"
	"src/exchange/stock.cpp"
	"src/exchange/stockcontroller.cpp"
	"src/exchange/utility.cpp"
)

set(simulationSRCS
	"src/simulation/agent.cpp"
	"src/simulation/simulation.cpp"
)

set(guiSRCS
	"src/gui/mainwindow.ui"
	"src/gui/mainwindow.cpp"
)

set(marketsimSRCS
	"src/main.cpp"
)

set(testSRCS
	"test/test.cpp"
	"test/exchange/accountcontroller_tests.cpp"
	"test/exchange/stockcontroller_tests.cpp"
)

add_library(exchange SHARED ${exchangeSRCS})

add_library(simulation SHARED ${simulationSRCS})
target_link_libraries(simulation exchange)

add_library(gui SHARED ${guiSRCS})
target_link_libraries(gui Qt5::Widgets)

add_executable(marketsim ${marketsimSRCS})
target_link_libraries(marketsim exchange gui simulation Qt5::Widgets ${LUA_LIBRARIES})

add_executable(test ${testSRCS})
target_link_libraries(test exchange ${CMAKE_THREAD_LIBS_INIT} ${LUA_LIBRARIES})
