#ifndef GAME_H
#define GAME_H
#include "../includes/Board.hpp"

class Game
{
    public:
    Game();
    ~Game();

    Board* getBoard() const;
    Pawn getCurrentPlayer() const;
    void togglePlayer();
    void readAndPlayFromSTDin();

    private:
    Pawn currentPlayer;
    Board *b;
};

#endif