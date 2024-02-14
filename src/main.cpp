#include <iostream>
#include <chrono>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/Player.hpp"
#include "../includes/MinMax.hpp"
#include "../includes/Random.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Game game;
    
    //Player player(Pawn::WHITE);
    //MinMax minmax(Pawn::BLACK);

    Random r1(Pawn::BLACK);
    Random r2(Pawn::WHITE);
    
    game.startGame(r1, r2);
    game.analyseGame(true);

    return 0;
}