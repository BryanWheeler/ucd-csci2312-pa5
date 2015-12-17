
#include "Agent.h"
#include "Resource.h"

const double Gaming::Agent::AGENT_FATIGUE_RATE = 0.3;


void Gaming::Agent::age() {
    if(this->__energy <= 0.000001){
        this->__energy = 0.0;
        this->finish();
    }
    else {
        this->__energy -= AGENT_FATIGUE_RATE;
    }
}

//No Default constructor so higher Class constructor used
Gaming::Agent::Agent(const Gaming::Game &g, const Gaming::Position &p, double energy)
:Piece(g, p)
{
    this->__energy = energy;
}

Gaming::Piece &Gaming::Agent::operator*(Gaming::Piece &other) {

    if(other.getType() == SIMPLE || other.getType() == STRATEGIC){
        return this->interact(dynamic_cast<Agent *>(&other));
    }
    else if(other.getType() == ADVANTAGE || other.getType() == FOOD){
        return this->interact(dynamic_cast<Resource *>(&other));
    }
    return *this;

}

Gaming::Piece &Gaming::Agent::interact(Gaming::Agent *agent) {
    if(this->__energy < agent->__energy){
        agent->__energy -= this->__energy;
        this->__energy = 0;
        this->finish();
        return * agent;
    }
    else if(agent->__energy < this->__energy){
        this->__energy -= agent->__energy;
        agent->__energy = 0;
        agent->finish();
        return * this;
    }
    else{
        this->__energy = 0;
        this->finish();
        agent->__energy = 0;
        agent->finish();
        return * this;
    }
}

Gaming::Piece &Gaming::Agent::interact(Gaming::Resource *resource) {
    this->__energy += resource->consume();
    return * this;
}

Gaming::Agent::~Agent() {

}
