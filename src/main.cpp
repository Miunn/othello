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
    if (argc < 3)
    {
        cout << "[ERROR] Invalid number of arguments" << endl;
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
        cout << "[ERROR] Invalid player 1 argument" << endl;
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
        cout << "[ERROR] Invalid player 2 argument" << endl;
        return 0;
    }

    bool benchmark = false;
    int benchmarkAmount = 0;

    bool displayGridResult = false;

    for (int i = 3; i < argc; i++)
    {
        if (((string)"--benchmark").compare(argv[i]) == 0)
        {
            if (i + 1 >= argc)
            {
                cout << "[ERROR] Missing benchmark param" << endl;
                return 0;
            }

            benchmarkAmount = atoi(argv[i+1]);
            benchmark = true;
        }

        if (((string)"--display-grid").compare(argv[i]) == 0)
        {
            displayGridResult = true;
        }
    }

    if (benchmark)
    {
        int blacksWons = 0;
        int whiteWons = 0;
        unsigned long int gameDurations = 0;
        for (int i = 0; i < benchmarkAmount; i++)
        {
            Game game;

            auto t1 = chrono::high_resolution_clock::now();
            game.startGame(*interface1, *interface2);
            auto t2 = chrono::high_resolution_clock::now();
            gameDurations += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
            
            cout << "==== Game " << setw(5) << i+1 << "/" << benchmarkAmount << " ====" << endl;
            Pawn winner = game.analyseGame(displayGridResult);

            if (winner == Pawn::BLACK)
            {
                blacksWons++;
            }
            else if (winner == Pawn::WHITE)
            {
                whiteWons++;
            }
        }

        cout << "\n====== Résultats ======" << endl;
        cout << "[NOIRS ] Victoires: " << blacksWons << " (" << blacksWons/(double)benchmarkAmount*100 << "%)" << endl;
        cout << "[BLANCS] Victoires: " << whiteWons << " (" << whiteWons/(double)benchmarkAmount*100 << "%)"  << endl;
        cout << "[EXEC  ] Temps moyen d'une partie: " << gameDurations / benchmarkAmount << " \xC2\xB5s" << endl;
    }
    else
    {
        Game game;
        game.startGame(*interface1, *interface2);
        game.analyseGame(displayGridResult);
    }

    return 0;
}