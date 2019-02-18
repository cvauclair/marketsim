#include "simulation.h"

Simulation::Simulation(Exchange &exchange, unsigned int numAgents)
{
	for(unsigned int i = 0; i < numAgents; i++){
		this->agents_.emplace_back(exchange);
	}
}

Simulation::~Simulation()
{
	delete this->t;
}

void Simulation::start()
{
	this->t = new std::thread(&Simulation::run, this);
}

void Simulation::run()
{
	while(!this->stop_){
		for(Agent &agent: this->agents_){
			agent.doAction();
		}
	}
}

void Simulation::stop()
{
	this->stop_ = true;
	this->t->join();
}
