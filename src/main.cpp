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
    MinMax *minmax = new MinMax(5, Strategy::ABSOLU);
    MinMax *minmax2 = new MinMax(Pawn::WHITE, 5, Strategy::POSITIONNEL);
    Game game;

    std::cout << game.getBoard()->coordToIndex("b3") << std::endl;

    std::cout << "Before" << std::endl;
    std::cout << minmax->play(*game.getBoard()) << std::endl;
    std::cout << "Played" << std::endl;

    game.startGame(*minmax, *minmax2);

    std::cout << *game.getBoard() << std::endl;

    return 0;
}