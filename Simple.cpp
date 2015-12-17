
#include "Simple.h"

const char Gaming::Simple::SIMPLE_ID = 'S';

void Gaming::Simple::print(std::ostream &os) const {
    os << SIMPLE_ID << this->__id;
}

Gaming::Simple::Simple(const Gaming::Game &g, const Gaming::Position &p, double energy)
: Gaming::Agent(g, p, energy)
{
//couldn't use regular means of __game(g), __position(p, etc. :(
}

Gaming::ActionType Gaming::Simple::takeTurn(const Gaming::Surroundings &s) const {
    ActionType ac;
    bool found = false;
    for (int i = 0; i < 9; i++){
        if(s.array[i] == SIMPLE || s.array[i] == STRATEGIC){
            //Do Nothing...
        }
        else if(s.array[i] == ADVANTAGE || s.array[i] == FOOD){
            switch(i){
                case 0: ac = NW;
                    found = true;
                    break;
                case 1: ac = N;
                    found = true;
                    break;
                case 2: ac = NE;
                    found = true;
                    break;
                case 3: ac = W;
                    found = true;
                    break;
                case 5: ac = E;
                    found = true;
                    break;
                case 6: ac = SW;
                    found = true;
                    break;
                case 7: ac = S;
                    found = true;
                    break;
                case 8: ac = SE;
                    found = true;
                    break;
            }
        }
        if(found == true){
            i = 9;
        }
    }
    if(found == false){
        for(int k = 0; k < 9; k++){
            if(s.array[k] == EMPTY){
                switch(k){
                    case 0: ac = NW;
                        found = true;
                        break;
                    case 1: ac = N;
                        found = true;
                        break;
                    case 2: ac = NE;
                        found = true;
                        break;
                    case 3: ac = W;
                        found = true;
                        break;
                    case 5: ac = E;
                        found = true;
                        break;
                    case 6: ac = SW;
                        found = true;
                        break;
                    case 7: ac = S;
                        found = true;
                        break;
                    case 8: ac = SE;
                        found = true;
                        break;
                }
            }
            if(found == true){
                k = 9;
            }
        }
    }
    if(found == false){
        ac = STAY;
    }


    return ac;
}

Gaming::Simple::~Simple() {

}
