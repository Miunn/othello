#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "../includes/Board.hpp"

class Game
{
    public:
    Game();
    ~Game();

    Board* getBoard() const;
    Pawn getCurrentPlayer() const;
    void togglePlayer();
    std::string readAndPlayFromSTDin();
    void startGame();

    private:
    Pawn currentPlayer;
    Board *b;
    bool runningGame;
};

#endif