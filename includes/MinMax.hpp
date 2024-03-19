#ifndef MINMAX_H
#define MINMAX_H
#include <iostream>
#include "AInterface.hpp"

class MinMax : public AInterface
{
public:
    MinMax(int depth);
    MinMax(Pawn player, int depth);
    int heuristic(const Board &board) const;
    int play_research(const Board &board, int depth, Pawn maxPawn) const;
    std::vector<Board*> computeSubBoards(const Board &board) const;
    std::string play(const Board &board) const override;

private:
    int depth;
};

#endif