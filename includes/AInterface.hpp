#ifndef AINTERFACE_H
#define AINTERFACE_H
#include <iostream>
#include "Board.hpp"

class AInterface
{
    public:
    virtual std::string play(const Board& board) const = 0;

    private:
    Pawn player;
};

#endif