#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "AInterface.hpp"

class Player : public AInterface
{
    public:
    Player();
    Player(Pawn player);
    std::string play(const Board& board) const override;
};

#endif