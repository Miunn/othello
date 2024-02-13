#include <iostream>
#include <chrono>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/Player.hpp"
#include "../includes/MinMax.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Game game;
    
    Player player(Pawn::WHITE);
    MinMax minmax(Pawn::BLACK);
    
    game.startGame(minmax, player);

    return 0;
}