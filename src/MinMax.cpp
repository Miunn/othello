#include <iostream>
#include "../includes/MinMax.hpp"

MinMax::MinMax()
{
    this->player = Pawn::BLACK;
}

MinMax::MinMax(Pawn player)
{
    this->player = player;
}

std::string MinMax::play(const Board& board) const
{
    return board.getValidMoves(this->player)[0];
}