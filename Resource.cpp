#include "Resource.h"
#include "Advantage.h"
#include "Agent.h"
#include "Simple.h"

namespace Gaming {
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;


    double Resource::consume() {
        //copy of resource capacity to return while zero-ing out the original capacity
        double resource = this->__capacity;
        this->__capacity = 0.0;
        this->finish();

        return resource;

    }

    void Gaming::Resource::age() {
        if (this->__capacity <= 0.01) {
            this->__capacity = 0.0;
            this->finish();
        }
        else {
            this->__capacity /= RESOURCE_SPOIL_FACTOR;
        }

    }

//Class doesn't have default constructor so need to call higher Class constructor i.e. Piece
    Gaming::Resource::Resource(const Gaming::Game &g, const Gaming::Position &p, double __capacity) : Piece(g, p) {
        this->__capacity = __capacity;
    }

    Gaming::ActionType Gaming::Resource::takeTurn(const Gaming::Surroundings &s) const {
        //Resources don't move
        return STAY;
    }

    Gaming::Piece &Gaming::Resource::operator*(Gaming::Piece &other) {
        //??? Do I do anything?
        return other;
    }

    Gaming::Piece &Gaming::Resource::interact(Gaming::Agent *agent) {
        if (this->getType() == FOOD) {
            dynamic_cast<Simple *>(agent)->addEnergy(this->consume());
        }
        else if (this->getType() == ADVANTAGE) {
            dynamic_cast<Simple *>(agent)->addEnergy(dynamic_cast<Advantage *>(this)->consume());
        }
        this->finish();
        this->__capacity = 0.0;

        return *this;
    }

    Gaming::Piece &Gaming::Resource::interact(Gaming::Resource *resource) {
        return *this;
    }

    Resource::~Resource() {

    }
}