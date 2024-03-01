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

int MinMax::heuristic(const Board &B) const
{
    int score = 0;
    for (int i = 0; i < B.getSize(); i++)
    {
        for (int j = 0; j < B.getSize(); j++)
        {
            int c = i * B.getSize() + j;
            if (B.getCoord(c) == this->player)
            {
                score += this->payoff_matrix[c];
            }
        }
    }
    return score;
}

std::string MinMax::play(const Board &board) const
{
    return board.getValidMoves(this->player)[0];
}