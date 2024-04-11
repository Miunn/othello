#ifndef ALPHABETA_H
#define ALPHABETA_H
#include <iostream>
#include "AInterface.hpp"

class AlphaBeta : public AInterface
{
public:
    AlphaBeta(int depth);
    AlphaBeta(Pawn player, int depth);
    int heuristic(const Board &board) const;
    std::vector<Board *> computeSubBoards(const Board &board) const;
    std::string play(const Board &board) const override;
    int play_research(const Board &board, int depth, int alpha, int beta, Pawn maxPawn) const;

private:
    int depth;
};

#endif