
#include "Advantage.h"

const char Gaming::Advantage::ADVANTAGE_ID = 'D';
const double Gaming::Advantage::ADVANTAGE_MULT_FACTOR = 2.0;


void Gaming::Advantage::print(std::ostream &os) const {
    os << ADVANTAGE_ID << this->__id;

}

//No Default constructor so high Class constructor used.  Advantage uses a multiplier for capacity
Gaming::Advantage::Advantage(const Gaming::Game &g, const Gaming::Position &p, double capacity)
:Resource(g, p, capacity * ADVANTAGE_MULT_FACTOR)
{

}

double Gaming::Advantage::getCapacity() const {
    return __capacity;
}


double Gaming::Advantage::consume() {
    //copy used to keep capacity while zero-ing out original capacity
    double resource = __capacity * ADVANTAGE_MULT_FACTOR;
    this->__capacity = 0.0;
    this->finish();

    return resource;
}

Gaming::Advantage::~Advantage() {

}
