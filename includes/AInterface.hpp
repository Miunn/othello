#ifndef AINTERFACE_H
#define AINTERFACE_H
#include <iostream>
#include "Board.hpp"

class AInterface
{
    public:
    virtual std::string play(const Board& board) const = 0;
    void showScores() const;

    protected:
    Pawn player;
    int scores[64] = {
        500, -150, 30, 10, 10, 30, -150, 500,
        -150, -250, 0, 0, 0, 0, -250, -150,
        30, 0, 1, 2, 2, 1, 0, 30,
        10, 0, 2, 16, 16, 2, 0, 10,
        10, 0, 2, 16, 16, 2, 0, 10,
        30, 0, 1, 2, 2, 1, 0, 30,
        -150, -250, 0, 0, 0, 0, -250, -150,
        500, -150, 30, 10, 10, 30, -150, 500
    };
};

#endif