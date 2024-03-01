#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/Player.hpp"
#include "../includes/MinMax.hpp"
#include "../includes/Random.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    MinMax *minmax = new MinMax();
    Game game;
    game.getBoard()->play(Pawn::BLACK, "d3");

    cout << minmax->heuristic(*game.getBoard()) << endl;
    return 0;
}