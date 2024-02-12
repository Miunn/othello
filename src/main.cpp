#include <iostream>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"

#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{

    Game game;

    cout << *game.getBoard() << endl;
        
    game.startGame();
    cout << *game.getBoard() << endl;

    return 0;
}