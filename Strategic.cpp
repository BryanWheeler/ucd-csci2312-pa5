
#include "Strategic.h"


const char Gaming::Strategic::STRATEGIC_ID = 'T';

void Gaming::Strategic::print(std::ostream &os) const {
    os << STRATEGIC_ID << this->__id;

}

Gaming::Strategic::Strategic(const Gaming::Game &g, const Gaming::Position &p, double energy, Gaming::Strategy *s)
:Gaming::Agent(g, p, energy)
{
    __strategy = s;

}

Gaming::ActionType Gaming::Strategic::takeTurn(const Gaming::Surroundings &s) const {

    return (*__strategy)(s);

}

Gaming::Strategic::~Strategic() {
    delete __strategy;
    //just doing anything to make this thing compile
}
