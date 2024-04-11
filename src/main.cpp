#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/Player.hpp"
#include "../includes/MinMax.hpp"
#include "../includes/AlphaBeta.hpp"
#include "../includes/Random.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    MinMax *minmax = new MinMax(Pawn::WHITE, 5);
    // Player *player = new Player(Pawn::WHITE);
    // Game game;

    // std::cout << "Before" << std::endl;
    // std::cout << minmax->play(*game.getBoard()) << std::endl;
    // std::cout << "Played" << std::endl;

    // game.startGame(*minmax, *player);

    AlphaBeta *alphaBeta = new AlphaBeta(Pawn::BLACK, 5);
    Player *player = new Player(Pawn::WHITE);

    Game game;

    std::cout << game.getBoard()->coordToIndex("b3") << std::endl;

    std::cout << "Before" << std::endl;
    std::cout << alphaBeta->play(*game.getBoard()) << std::endl;
    std::cout << "Played" << std::endl;

    game.startGame(*alphaBeta, *minmax);
    std::cout << game.analyseGame(true, true) << std::endl;

    return 0;
}