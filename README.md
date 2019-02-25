# marketsim

A C++ stock market simulator

## Overview
Note: This is a work in progress and the features listed below are what the project intends to be.

**marketsim** is an agent based stock market simulator which features three main components: 
* The exchange server, which receives bid and ask offers, matches buyers and sellers and hold the account information of all market participants
* The simulation client, which interacts with the exchange server to simulate realistic market agent behavior
* A GUI client to observe the stock market in real time

### Currently implemented features
* The exchange and simulation running in parallel in the same process
* The exchange featuring only one stock
* A mostly random simulation of ask and bid offers

### Planned features (in the short-term)
* Client-server separation
* GUI client to observe the stock market in real time
* Ability to have multiple stocks listed on the exchange server
* More realistic agent behavior
* Lua config files

### Planned features (in the long-term)
* Support for more financial instruments (e.g.: stock options and futures)

## Building
Dependencies:
* Qt5 library (for the GUI client)
* Catch2 (for the tests)

The exchange server and simulation client have no dependencies. The GUI client and tests can be commented out of the CMakeLists.txt file if one does not wish to compile those.

To build the software, simply run the following commands from the project's directory:
```
mkdir build
cd build
cmake ..
make
```

## Running
To run the simulation, simply execute the `marketsim` program located in the `build/` directory (after building the project).