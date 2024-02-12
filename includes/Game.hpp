#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "../includes/Board.hpp"

class Game
{
    public:
    Game();
    Game(Board *b, Pawn player);
    ~Game();

    Board* getBoard() const;
    Pawn getCurrentPlayer() const;
    std::vector<std::string> togglePlayer();
    std::string readAndPlayFromSTDin();
    void startGame();

    private:
    Pawn currentPlayer;
    Board *b;
    bool runningGame;
};

#endif