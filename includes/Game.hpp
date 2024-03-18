#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "../includes/Board.hpp"
#include "../includes/AInterface.hpp"

/**
 * @brief Othello Game class
 * 
 */
class Game
{
    public:

    /**
     * @brief Construct a new Game object
     * Init a new board and set the current player to BLACK
     */
    Game();

    /**
     * @brief Copy a new Game object
     * 
     * @param b Board to copy
     * @param player Player to set
     */
    Game(Board *b, Pawn player);

    /**
     * @brief Destroy the Game object
     * 
     */
    ~Game();

    /**
     * @brief Get the Board object
     * 
     * @return Board* 
     */
    Board* getBoard() const;

    /**
     * @brief Get the Current Player
     * 
     * @return Pawn 
     */
    Pawn getCurrentPlayer() const;

    /**
     * @brief Read a move from stdin and try to play it
     * 
     * @return std::string Played move
     */
    std::string readAndPlayFromSTDin();

    /**
     * @brief Start a new othello game
     * 
     */
    void startGame(const AInterface& interface1, const AInterface& interface2);

    /**
     * @brief Analyse a finished game. Giving scores and winner
     * 
     * @param displayGrid Tells if the function should display the finished board
     * @return Pawn Winner pawn
     */
    Pawn analyseGame(bool verbose, bool displayGrid) const;

    private:

    /**
     * @brief Game board object
     * 
     */
    Board *b;

    /**
     * @brief Tells if the game is running or not
     * 
     */
    bool runningGame;
};

#endif