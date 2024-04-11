#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/Player.hpp"
#include "../includes/MinMax.hpp"
#include "../includes/Random.hpp"
#include "../includes/AlphaBeta.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "[ERROR] Invalid number of arguments" << endl;
        return 0;
    }

    AInterface *interface1;
    AInterface *interface2;
    if (((string) "player").compare(argv[1]) == 0)
    {
        interface1 = new Player(Pawn::BLACK);
    }
    else if (((string) "random").compare(argv[1]) == 0)
    {
        interface1 = new Random(Pawn::BLACK);
    }
    else if (((string) "minmax").compare(argv[1]) == 0)
    {
        interface1 = new MinMax(Pawn::BLACK, 3, Strategy::POSITIONNEL);
    }
    else if (((string) "alphabeta").compare(argv[1]) == 0)
    {
        interface1 = new AlphaBeta(Pawn::BLACK, 3, Strategy::POSITIONNEL);
    }
    else
    {
        cout << "[ERROR] Invalid player 1 argument" << endl;
        return 0;
    }

    if (((string) "player").compare(argv[2]) == 0)
    {
        interface2 = new Player(Pawn::WHITE);
    }
    else if (((string) "random").compare(argv[2]) == 0)
    {
        interface2 = new Random(Pawn::WHITE);
    }
    else if (((string) "minmax").compare(argv[2]) == 0)
    {
        interface2 = new MinMax(Pawn::WHITE, 3, Strategy::POSITIONNEL);
    }
    else if (((string) "alphabeta").compare(argv[2]) == 0)
    {
        interface2 = new AlphaBeta(Pawn::WHITE, 3, Strategy::POSITIONNEL);
    }
    else
    {
        cout << "[ERROR] Invalid player 2 argument" << endl;
        return 0;
    }

    bool benchmark = false;
    int benchmarkAmount = 0;
    bool onlyFinal = false;

    bool displayGridResult = false;

    for (int i = 3; i < argc; i++)
    {
        if (((string) "--benchmark").compare(argv[i]) == 0)
        {
            if (i + 1 >= argc)
            {
                cout << "[ERROR] Missing benchmark param" << endl;
                return 0;
            }

            benchmarkAmount = atoi(argv[i + 1]);
            benchmark = true;
        }

        if (((string) "--display-grid").compare(argv[i]) == 0)
        {
            displayGridResult = true;
        }

        if (((string) "--only-final").compare(argv[i]) == 0)
        {
            onlyFinal = true;
        }
    }

    if (benchmark)
    {
        int blacksWons = 0;
        int whiteWons = 0;
        int draws = 0;
        unsigned long int gameDurations = 0;
        for (int i = 0; i < benchmarkAmount; i++)
        {
            Game game;
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
    else if (((string)"minmax").compare(argv[1]) == 0)
    {
        interface1 = new MinMax(Pawn::BLACK, 3, Strategy::POSITIONNEL);
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
    else if (((string)"minmax").compare(argv[2]) == 0)
    {
        interface2 = new MinMax(Pawn::WHITE, 3, Strategy::POSITIONNEL);
    }
    else
    {
        cout << "[ERROR] Invalid player 2 argument" << endl;
        return 0;
    }

    bool benchmark = false;
    int benchmarkAmount = 0;
    bool onlyFinal = false;

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

        if (((string)"--only-final").compare(argv[i]) == 0)
        {
            onlyFinal = true;
        }
    }

    if (benchmark)
    {
        int blacksWons = 0;
        int whiteWons = 0;
        int draws = 0;
        unsigned long int gameDurations = 0;
        for (int i = 0; i < benchmarkAmount; i++)
        {
            Game game;

            auto t1 = chrono::high_resolution_clock::now();
            game.startGame(*interface1, *interface2);
            auto t2 = chrono::high_resolution_clock::now();
            gameDurations += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
            
            if (!onlyFinal)
            {
                cout << "==== Game " << setw(5) << i+1 << "/" << benchmarkAmount << " ====" << endl;
            }
            else
            {
                cout << "\rGame " << i+1 << "/" << benchmarkAmount << std::flush;
            }

            Pawn winner = game.analyseGame(!onlyFinal, displayGridResult);

            if (winner == Pawn::BLACK)
            {
                blacksWons++;
            }
            else if (winner == Pawn::WHITE)
            {
                whiteWons++;
            }
            else
            {
                draws++;
            }
        }

        cout << "\n\n====== Résultats ======" << endl;
        cout << "[NOIRS ] Victoires: " << setw(6) << blacksWons << " (" << blacksWons/(double)benchmarkAmount*100 << "%)" << endl;
        cout << "[BLANCS] Victoires: " << setw(6) << whiteWons << " (" << whiteWons/(double)benchmarkAmount*100 << "%)"  << endl;
        cout << "[******] Egalités: " << setw(7) << draws << " (" << draws/(double)benchmarkAmount*100 << "%)"  << endl;
        cout << "[EXEC  ] Temps moyen d'une partie: " << gameDurations / benchmarkAmount / 1000.0 << "ms" << endl;
    }
    else
    {
        Game game;
        game.startGame(*interface1, *interface2);
        game.analyseGame(true, displayGridResult);
    }
            auto t1 = chrono::high_resolution_clock::now();
            game.startGame(*interface1, *interface2);
            auto t2 = chrono::high_resolution_clock::now();
            gameDurations += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

            if (!onlyFinal)
            {
                cout << "==== Game " << setw(5) << i + 1 << "/" << benchmarkAmount << " ====" << endl;
            }
            else
            {
                cout << "\rGame " << i + 1 << "/" << benchmarkAmount << std::flush;
            }

            Pawn winner = game.analyseGame(!onlyFinal, displayGridResult);

            if (winner == Pawn::BLACK)
            {
                blacksWons++;
            }
            else if (winner == Pawn::WHITE)
            {
                whiteWons++;
            }
            else
            {
                draws++;
            }
        }

        cout << "\n\n====== Résultats ======" << endl;
        cout << "[NOIRS ] Victoires: " << setw(6) << blacksWons << " (" << blacksWons / (double)benchmarkAmount * 100 << "%)" << endl;
        cout << "[BLANCS] Victoires: " << setw(6) << whiteWons << " (" << whiteWons / (double)benchmarkAmount * 100 << "%)" << endl;
        cout << "[******] Egalités: " << setw(7) << draws << " (" << draws / (double)benchmarkAmount * 100 << "%)" << endl;
        cout << "[EXEC  ] Temps moyen d'une partie: " << gameDurations / benchmarkAmount / 1000.0 << "ms" << endl;
    }
    else
    {
        Game game;
        game.startGame(*interface1, *interface2);
        game.analyseGame(true, displayGridResult);
    }

    return 0;
}