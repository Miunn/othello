#include <iostream>
#include "../includes/Board.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    Board b;

    cout << b << endl;
    
    std::vector<string> validBlack = b.getValidMove(WHITE);

    for (int i = 0; i < (int) validBlack.size(); i ++)
    {
        cout << validBlack[i] << " ";
    }
    cout << endl;

    b.place(Pawn::WHITE, "c3");
    b.place(Pawn::BLACK, "c4");
    b.place(Pawn::BLACK, "c5");
    b.place(Pawn::BLACK, "c6");
    
    b.place(Pawn::BLACK, "d6");
    b.place(Pawn::BLACK, "e5");
    b.place(Pawn::BLACK, "f4");
    b.place(Pawn::WHITE, "g3");
    
    b.place(Pawn::BLACK, "d7");
    b.place(Pawn::WHITE, "e7");

    cout << b << endl;

    vector<string> moves = b.getValidMove(Pawn::WHITE);
    for (int i = 0; i < (int)moves.size(); i++) {
        cout << moves[i] << " ";
    }
    cout << endl << endl;

    b.play(Pawn::WHITE, "c7");

    cout << b << endl;

    //b.switchPawns(Pawn::BLACK, "c4", Direction::RIGHT);
    /*b.play(Pawn::BLACK, "c4");

    cout << b << endl;

    b.play(Pawn::WHITE, "e3");

    cout << b << endl;

    b.play(Pawn::BLACK, "f4");

    cout << b << endl;

    b.play(Pawn::WHITE, "c5");

    cout << b << endl;

    b.play(Pawn::BLACK, "e6");

    cout << b << endl;*/

    return 0;
}