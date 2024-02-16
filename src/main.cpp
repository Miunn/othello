#include <iostream>
#include <chrono>
#include <string>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/Player.hpp"
#include "../includes/MinMax.hpp"
#include "../includes/Random.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Invalid number of arguments" << endl;
        return 0;
    }

    AInterface* interface1;
    AInterface* interface2;
    if (((string)"player").compare(argv[1]) == 0)
    {
        interface1 = new Player(Pawn::BLACK);
    }
    else if (((string)"random").compare(argv[1]) == 0)
    {
        interface1 = new Random(Pawn::BLACK);
    }
    else
    {
        cout << "Invalid player 1 argument" << endl;
        return 0;
    }

    if (((string)"player").compare(argv[2]) == 0)
    {
        interface2 = new Player(Pawn::WHITE);
    }
    else if (((string)"random").compare(argv[2]) == 0)
    {
        interface2 = new Random(Pawn::WHITE);
    }
    else
    {
        cout << "Invalid player 2 argument" << endl;
        return 0;
    }

    Game game;
    game.startGame(*interface1, *interface2);
    game.analyseGame(true);

    return 0;
}