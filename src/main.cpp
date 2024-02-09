#include <iostream>
#include "../includes/Board.hpp"

#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{

    Board b;

    cout << b << endl;

    int all_durations = 0;
    for (int i = 0; i < 1000; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();
        b.getValidMove(Pawn::BLACK);
        auto t2 = std::chrono::high_resolution_clock::now();
        all_durations += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    }

    cout << "Find valid moves average exec time: " << all_durations / 1000 << " microseconds" << endl;

    /*vector<string> history = {};
    Pawn currentPlayer = Pawn::BLACK;
    for (vector<string> moves = b.getValidMove(currentPlayer); (int)moves.size() > 0; moves = b.getValidMove(currentPlayer)) {
        cout << b << endl;

        cout << "Play: " << moves[0] << endl;
        
        auto t1 = std::chrono::high_resolution_clock::now();
        if (!b.play(currentPlayer, moves[0])) {
            cout << "Play returned false" << endl;
            break;
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        cout << "Time to play " << duration.count() << " microseconds" << endl;

        history.push_back(moves[0]);
        if (currentPlayer == Pawn::BLACK) currentPlayer = Pawn::WHITE;
        else currentPlayer = Pawn::BLACK;
    }

    cout << b << endl << "Ended game, player " << currentPlayer << endl;
    cout << "History: ";
    for (int i = 0; i < (int)history.size(); i++) {
        cout << history[i] << " ";
    }
    cout << endl;*/

    return 0;
}