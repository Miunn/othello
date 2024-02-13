#include <iostream>
#include <chrono>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/MinMax.hpp"


using namespace std;

int main(int argc, char *argv[])
{
    Game game;
    
    MinMax minmax;
    minmax.showScores();

    return 0;
}