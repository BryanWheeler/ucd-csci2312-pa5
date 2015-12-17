
#include "Food.h"

const char Gaming::Food::FOOD_ID = 'F';

void Gaming::Food::print(std::ostream &os) const {
    os << FOOD_ID << this->__id;

}

//Default constructor not there so higher Class constructor used
Gaming::Food::Food(const Gaming::Game &g, const Gaming::Position &p, double capacity)
:Resource(g, p, capacity)
{
__capacity = capacity;
}


Gaming::Food::~Food() {

}
