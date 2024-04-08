#ifndef AINTERFACE_H
#define AINTERFACE_H
#include <iostream>
#include <string>
#include "Board.hpp"

typedef enum: unsigned short
{
  POSITIONNEL = 0,
  ABSOLU = 1,
  MOBILITE = 2,
} Strategy;

/**
 * @brief Interface for the differents AI algorithms of the project
 * 
 */
class AInterface
{
    public:
    /**
     * @brief Play a move on the board
     * 
     * @param board Copy of the board, its not the AI who modify the value, just research on it
     * @return std::string Coordinate to play
     */
    virtual std::string play(const Board& board) const = 0;

    /**
     * @brief Get the player for the interface
     * 
     * @return Pawn 
     */
    Pawn getPlayer() const;

    /**
     * @brief Display associated pay off matrix
     * 
     */
    void showScores() const;

    protected:
    /**
     * @brief Player played by the AI
     * 
     */
    Pawn player;

    Pawn ennemy;

    Strategy strategy;

    /**
     * @brief Pay off matrix
     * 
     */
    int payoff_matrix[64] = {
         500, -150, 30, 10, 10, 30, -150,  500,
        -150, -250,  0,  0,  0,  0, -250, -150,
          30,    0,  1,  2,  2,  1,    0,  30,
          10,    0,  2, 16, 16,  2,    0,  10,
          10,    0,  2, 16, 16,  2,    0,  10,
          30,    0,  1,  2,  2,  1,    0,  30,
        -150, -250,  0,  0,  0,  0, -250, -150,
         500, -150, 30, 10, 10, 30, -150,  500
    };
};

#endif