#ifndef MINMAX_H
#define MINMAX_H
#include <iostream>
#include "AInterface.hpp"

class MinMax: public AInterface
{
    public:
    MinMax();
    MinMax(Pawn player);
    std::string play(const Board& board) const;

    private:
    Pawn player;
};

#endif