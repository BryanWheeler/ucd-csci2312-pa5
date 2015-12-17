#include "Piece.h"

namespace Gaming {

    unsigned int Piece::__idGen = 0;

    Gaming::Piece::Piece(const Game &g, const Position &p)
            : __game(g), __position(p), __id(++__idGen), __finished(false) {

    }

    std::ostream &operator<<(std::ostream &os, const Gaming::Piece &piece) {
        piece.print(os);
        return os;
        //I think this works...
    }

    Piece::~Piece() {

    }
}