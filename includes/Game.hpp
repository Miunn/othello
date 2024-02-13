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
     * @brief Toggle the player. If no moves are possible for the player, skip his turn
     * If no moves available for both player, end the game by setting runningGame to false
     * 
     * @return std::vector<std::string> Moves available for the new player. Empty if game ended
     */
    std::vector<std::string> togglePlayer();

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

    private:

    /**
     * @brief Current player representation
     * 
     */
    Pawn currentPlayer;

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