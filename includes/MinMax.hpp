#ifndef MINMAX_H
#define MINMAX_H
#include <iostream>
#include "AInterface.hpp"

class MinMax : public AInterface
{
public:
    MinMax(int depth, Strategy strategy);
    MinMax(Pawn player, int depth, Strategy strategy);

    /**
     * @brief Get node value based with the given strategy
     * 
     * @param board Game board
     * @return int Computed node value
     */
    int heuristic(const Board &board, std::string move) const;

    /**
     * @brief Get node value for a positionnal strategy (func. called by heuristic)
     * 
     * @param board Game board
     * @return int Computed node value
     */
    int heuristic_pos(const Board &board) const;

    /**
     * @brief Get node value for an absolute strategy (func. called by heuristc)
     * 
     * @param board Game board
     * @return int Computed node value
     */
    int heuristic_abs(const Board &board) const;

    /**
     * @brief Get node value for a mobility strategy (func. called by heuristic)
     * 
     * @param board Game board
     * @param move Moved played to get this board
     * @return int Computed node value
     */
    int heuristic_mob(const Board &board, std::string move) const;

    /**
     * @brief Get node value for a mixed strategy (func. called by heuristic)
     * 
     * @param board Game board
     * @return int Computed node value
     */
    int heuristic_mixte(const Board &board, std::string move) const;

    int play_research(const Board &board, std::string move, int depth, Pawn maxPawn) const;
    std::vector<Board*> computeSubBoards(const Board &board) const;
    std::string play(const Board &board) const override;

private:
    int depth;
};

#endif