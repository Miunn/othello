#ifndef ALPHABETA_H
#define ALPHABETA_H
#include <iostream>
#include "AInterface.hpp"

class AlphaBeta : public AInterface
{
public:
    AlphaBeta(int depth, Strategy strategy);
    AlphaBeta(Pawn player, int depth, Strategy strategy);
    int heuristic(const Board &board) const;
    int heuristic_pos(const Board &board) const;
    int heuristic_abs(const Board &board) const;
    int heuristic_mob(const Board &board) const;
    std::vector<Board *> computeSubBoards(const Board &board) const;
    std::string play(const Board &board) const override;
    int play_research(const Board &board, int depth, int alpha, int beta, Pawn maxPawn) const;

private:
    int depth;
};

#endif