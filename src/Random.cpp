#include <iostream>
#include <random>
#include <ctime>
#include "../includes/Random.hpp"

Random::Random()
{
    srand(time(NULL));
    this->player = Pawn::BLACK;
}

Random::Random(Pawn player)
{
    srand(time(NULL));
    this->player = player;
}

std::string Random::play(const Board& board) const
{
    std::vector<std::string> moves = board.getValidMoves(this->player);
    return moves[rand() % moves.size()];
}