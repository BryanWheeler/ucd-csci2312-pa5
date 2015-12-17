#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Agent.h"
#include "Exceptions.h"
#include <iomanip>

namespace Gaming {
    const unsigned int Gaming::Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Gaming::Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned int Gaming::Game::MIN_WIDTH = 3;
    const unsigned int Gaming::Game::MIN_HEIGHT = 3;
    const double Gaming::Game::STARTING_AGENT_ENERGY = 20;
    const double Gaming::Game::STARTING_RESOURCE_CAPACITY = 10;


    void Gaming::Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        // simple pseudo-random number generator
// sufficient for our casual purposes
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

// populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }


        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }


        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }


        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }


    }

    Gaming::Game::Game() {

        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __grid.resize(__width * __height);
        __status = NOT_STARTED;
        __round = 0;

    }

    Gaming::Game::Game(const Gaming::Game &another) {
        this->__grid = another.__grid;

        this->__height = another.__height;
        this->__numInitAgents = another.__numInitAgents;
        this->__numInitResources = another.__numInitResources;
        this->__status = another.__status;
        this->__width = another.__width;
        this->__round = another.__round;
        this->__verbose = another.__verbose;
    }

    Gaming::Game::Game(unsigned width, unsigned height, bool manual) {
        if (width < MIN_WIDTH || height < MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }

        this->__width = width;
        this->__height = height;
        this->__grid.resize(__width * __height);
        this->__status = NOT_STARTED;
        this->__round = 0;

        if (manual) {
            //Do Nothing
        }
        else {
            populate();

        }

    }

    unsigned int Gaming::Game::getNumPieces() const {
        unsigned int pieces = 0;
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {
                ++pieces;
            }
        }
        return pieces;
    }

    unsigned int Gaming::Game::getNumSimple() const {
        // dynamic_cast returns a pointer of the argument type
// or NULL if the derived type of the object is not of
// the argument type
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *agent = dynamic_cast<Simple *>(*it);
            if (agent) numAgents++;
        }

        return numAgents;


    }

    unsigned int Gaming::Game::getNumStrategic() const {
        // dynamic_cast returns a pointer of the argument type
// or NULL if the derived type of the object is not of
// the argument type
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *agent = dynamic_cast<Strategic *>(*it);
            if (agent) numAgents++;
        }

        return numAgents;
    }

    unsigned int Gaming::Game::getNumAgents() const {
        return getNumSimple() + getNumStrategic();
    }

    unsigned int Game::getNumResources() const {
        // dynamic_cast returns a pointer of the argument type
// or NULL if the derived type of the object is not of
// the argument type
        unsigned int numFood = 0;
        unsigned int numAdvantage = 0;
        unsigned int resources = 0;

        for(int i = 0; i < __grid.size(); i++){
            if(__grid[i] != nullptr){
                if(__grid[i]->getType() == PieceType::ADVANTAGE || __grid[i]->getType() == PieceType::FOOD){
                    resources++;
                }
            }
        }
        /*
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *piece = dynamic_cast<Food *>(*it);
            if (piece) numFood++;
        }
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *piece = dynamic_cast<Advantage *>(*it);
            if (piece) numAdvantage++;
        }
        */


        //return numFood + numAdvantage;
        return resources;
    }

    bool Game::addSimple(const Gaming::Position &position) {
        if (position.y >= __width || position.x >= __height) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (__grid[position.x * __width + position.y] != nullptr) {
            return false;
        }
        else if (__grid[position.x * __width + position.y] == nullptr) {
            __grid[position.x * __width + position.y] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
            return true;

        }
        return false;
    }

    bool Game::addSimple(unsigned x, unsigned y) {
        if (y >= __width || x >= __height) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        const Position pos(x, y);
        if (__grid[x * __width + y] != nullptr) {
            return false;
        }
        else if (__grid[x * __width + y] == nullptr) {
            __grid[x * __width + y] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
            return true;
        }

        return false;
    }

    bool Gaming::Game::addStrategic(const Gaming::Position &position, Gaming::Strategy *s) {
        if (position.y >= __width || position.x >= __height) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (__grid[position.x * __width + position.y] != nullptr) {
            return false;
        }
        else if (__grid[position.x * __width + position.y] == nullptr) {
            __grid[position.x * __width + position.y] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
            return true;
        }

        return false;
    }

    bool Gaming::Game::addStrategic(unsigned x, unsigned y, Gaming::Strategy *s) {

        if (y >= __width || x >= __height) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position pos(x, y);

        if (__grid[x * __width + y] != nullptr) {
            return false;
        }
        else if (__grid[x * __width + y] == nullptr) {
            __grid[x * __width + y] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY, s);
            return true;
        }

        return false;
    }

    bool Gaming::Game::addFood(const Gaming::Position &position) {
        if (position.y >= __width || position.x >= __height) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (__grid[position.x * __width + position.y] != nullptr) {
            return false;
        }
        else if (__grid[position.x * __width + position.y] == nullptr) {
            __grid[position.x * __width + position.y] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
            return true;
        }

        return false;
    }

    bool Gaming::Game::addFood(unsigned x, unsigned y) {
        if (y >= __width || x >= __height) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position pos(x, y);

        if (__grid[x * __width + y] != nullptr) {
            return false;
        }
        else if (__grid[x * __width + y] == nullptr) {
            __grid[x * __width + y] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
            return true;
        }

        return false;
    }

    bool Gaming::Game::addAdvantage(const Gaming::Position &position) {
        if (position.y >= __width || position.x >= __height) {
            throw OutOfBoundsEx(__width, __height, position.y, position.x);
        }
        if (__grid[position.x * __width + position.y] != nullptr) {
            return false;
        }
        else if (__grid[position.x * __width + position.y] == nullptr) {
            __grid[position.x * __width + position.y] = new Advantage(*this, position,
                                                                      Game::STARTING_RESOURCE_CAPACITY);
            return true;
        }

        return false;
    }

    bool Gaming::Game::addAdvantage(unsigned x, unsigned y) {
        if (y >= __width || x >= __height) {
            throw OutOfBoundsEx(__width, __height, y, x);
        }
        const Position pos(x, y);

        if (__grid[x * __width + y] != nullptr) {
            return false;
        }
        else if (__grid[x * __width + y] == nullptr) {
            __grid[x * __width + y] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
            return true;
        }

        return false;
    }

//LOOK BACK AT THIS TO TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    const Gaming::Surroundings Gaming::Game::getSurroundings(const Gaming::Position &pos) const {
        int element = 0;
        Gaming::Surroundings surrounding;
        PieceType type;
        int x = pos.x;
        int y = pos.y;
        for (int i = x - 1; i <= x + 1; i++) {
            for (int k = y - 1; k <= y + 1; k++) {
                if (i * __width + k > __width * __height || i * __width + k < 0) {
                    surrounding.array[element] = INACCESSIBLE;
                    ++element;
                }

                else if (k >= __width || i >= __height) {
                    surrounding.array[element] = INACCESSIBLE;
                    ++element;
                }
                else if (i == pos.x && k == pos.y) {
                    surrounding.array[element] = SELF;
                    ++element;
                }
                else if (__grid[i * __width + k] == nullptr) {
                    surrounding.array[element] = EMPTY;
                    ++element;
                }
                else {
                    type = __grid[i * __width + k]->getType();
                    surrounding.array[element] = type;
                    ++element;
                }


            }
        }
        return surrounding;
    }

    const Gaming::ActionType Gaming::Game::reachSurroundings(const Gaming::Position &from, const Gaming::Position &to) {
        if (to.x == from.x - 1) {
            if (to.y == from.y - 1) {
                return NW;
            }
            else if (to.y == from.y) {
                return N;
            }
            else if (to.y == from.y + 1) {
                return NE;
            }
        }
        else if (to.x == from.x) {
            if (to.y == from.y - 1) {
                return W;
            }
            else if (to.y == from.y) {
                return STAY;
            }
            else if (to.y == from.y + 1) {
                return E;
            }
        }
        else if (to.x == from.x + 1) {
            if (to.y == from.y - 1) {
                return SW;
            }
            else if (to.y == from.y) {
                return S;
            }
            else if (to.y == from.y + 1) {
                return SE;
            }
        }
        else {
            return STAY;
        }
        return STAY;

    }


    bool Gaming::Game::isLegal(const Gaming::ActionType &ac, const Gaming::Position &pos) const {

        bool result;
        Gaming::Surroundings surrounding = getSurroundings(pos);
        switch (ac) {
            case NW:
                if (surrounding.array[0] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }

                break;
            case N:
                if (surrounding.array[1] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }

                break;

            case NE:
                if (surrounding.array[2] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }
                break;

            case W:
                if (surrounding.array[3] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }
                break;

            case STAY:
                if (surrounding.array[4] == SELF) {
                    result = true;
                }
                break;

            case E:
                if (surrounding.array[5] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }
                break;

            case SW:
                if (surrounding.array[6] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }
                break;

            case S:
                if (surrounding.array[7] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }
                break;

            case SE:
                if (surrounding.array[8] == INACCESSIBLE) {
                    result = false;
                }
                else {
                    result = true;
                }

        }

        return result;

    }

    const Gaming::Position Gaming::Game::move(const Gaming::Position &pos, const Gaming::ActionType &ac) const {
        if (isLegal(ac, pos)) {
            if (ac == NW) {
                return Position(pos.x - 1, pos.y - 1);
            }
            else if (ac == N) {
                return Position(pos.x - 1, pos.y);
            }
            else if (ac == NE) {
                return Position(pos.x - 1, pos.y + 1);
            }
            else if (ac == W) {
                return Position(pos.x, pos.y - 1);
            }
            else if (ac == E) {
                return Position(pos.x, pos.y + 1);
            }
            else if (ac == SW) {
                return Position(pos.x + 1, pos.y - 1);
            }
            else if (ac == S) {
                return Position(pos.x + 1, pos.y);
            }
            else if (ac == SE) {
                return Position(pos.x + 1, pos.y + 1);
            }
            else {
                return pos;
            }
        }

        else {
            return pos;

        }
    }

    void Gaming::Game::round() {
        bool from = false;
        bool to = false;
        ++__round;
        Gaming::ActionType ac;
        Gaming::Position posTo, posFrom;

        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] == nullptr) {
                //Do Nothing
            }
            else {
                if (__grid[i]->getTurned()) {
                    //Do Nothing
                }
                else {
                    __grid[i]->setTurned(true);
                    posFrom = __grid[i]->getPosition();
                    ac = __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()));
                    posTo = move(__grid[i]->getPosition(), ac);
                    if(posTo.x == posFrom.x && posTo.y == posFrom.y) {
                        //Do Nothing
                    }
                    else if(posTo.x != posFrom.x || posTo.y == posFrom.y)
                            __grid[i]->setPosition(posTo);



                    if (__grid[posTo.x * __width + posTo.y] != nullptr) {
                        *__grid[i] * (*__grid[posTo.x * __width + posTo.y]);
                        if (!__grid[i]->isViable()) {
                            delete __grid[i];
                            from = true;
                        }

                        if (!__grid[posTo.x * __width + posTo.y]->isViable()) {
                            delete __grid[posTo.x * __width + posTo.y];
                            to = true;
                        }
                        if (from && to) {
                            __grid[posTo.x * __width + posTo.y] = nullptr;
                        }
                        if (!from) {
                            __grid[posTo.x * __width + posTo.y] = __grid[i];
                        }
                        if (ac != STAY) {
                            __grid[i] = nullptr;
                        }


                    }

                }

            }
        }
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] == nullptr) {
                //Do Nothing
            }
            else {
                __grid[i]->age();
                __grid[i]->setTurned(false);
                if (!__grid[i]->isViable()) {
                    delete __grid[i];
                }
            }
        }
    }








    Gaming::Game::~Game() {
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {
                delete __grid[i];
            }
        }

    }

    std::ostream &operator<<(std::ostream &os, const Gaming::Game &game) {

        os << "Round " << game.__round << std::endl;
        for (int i = 0; i < game.__height; i++) {
            for (int j = 0; j < game.__width; j++) {
                os << "[";
                if (game.__grid[i * game.__width + j] != nullptr) {
                    os << *(game.__grid[i * game.__width + j]);
                }
                else {
                    os << "     ";
                }
                os << "]";

            }

            os << std::endl;
        }
            os << "Status: " << game.__status << std::endl;

    }



    void Gaming::Game::play(bool verbose) {

        __verbose = verbose;
        __status = PLAYING;

        while (getNumResources() != 0) {
            this->round();
            //If verbose is true and resources > 0 then prints
            if (__verbose != false && getNumResources() != 0) {
                std::cout << *this;
            }
        }
        __status = OVER;
        //If verbose is true then prints the last round
        if (verbose) {
            std::cout << *this;
        }

    }

}

