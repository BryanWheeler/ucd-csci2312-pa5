
#include "AggressiveAgentStrategy.h"
#include "Game.h"

const double Gaming::AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;


Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
:__agentEnergy(agentEnergy)
{

}

Gaming::ActionType Gaming::AggressiveAgentStrategy::operator()(const Gaming::Surroundings &s) const {
    ActionType ac;
    bool found = false;
    if(__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD){
        for(int w = 0; w < 9; w++){
            if (s.array[w] == SIMPLE || s.array[w] == STRATEGIC){
                switch(w){
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
                w = 9;
            }
        }
    }
    if(found == false) {
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == ADVANTAGE) {
                switch (i) {
                    case 0:
                        ac = NW;
                        found = true;
                        break;
                    case 1:
                        ac = N;
                        found = true;
                        break;
                    case 2:
                        ac = NE;
                        found = true;
                        break;
                    case 3:
                        ac = W;
                        found = true;
                        break;
                    case 5:
                        ac = E;
                        found = true;
                        break;
                    case 6:
                        ac = SW;
                        found = true;
                        break;
                    case 7:
                        ac = S;
                        found = true;
                        break;
                    case 8:
                        ac = SE;
                        found = true;
                        break;
                }
            }
            if (found == true) {
                i = 9;
            }
        }
    }
    if(found == false){
        for(int k = 0; k < 9; k++){
            if(s.array[k] == FOOD){
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
        for(int j = 0; j < 9; j++){
            if(s.array[j] == EMPTY){
                switch(j){
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
                j = 9;
            }
        }
    }

    if(found == false){
        ac = STAY;
    }


    return ac;
}

Gaming::AggressiveAgentStrategy::~AggressiveAgentStrategy() {

}
