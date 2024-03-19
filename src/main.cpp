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
    MinMax *minmax = new MinMax(5);
    Game game;

    std::cout << minmax->play(*game.getBoard()) << std::endl;

    return 0;
}