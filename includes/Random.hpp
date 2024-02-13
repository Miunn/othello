#ifndef RANDOM_H
#define RANDOM_H
#include "../includes/AInterface.hpp"

class Random : public AInterface
{
    public:
    Random();
    Random(Pawn player);
    std::string play(const Board& board) const override;
};

#endif