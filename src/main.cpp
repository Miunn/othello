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

    //b.switchPawns(Pawn::BLACK, "c4", Direction::RIGHT);
    b.place(Pawn::BLACK, "c4");

    cout << b << endl;

    b.place(Pawn::WHITE, "e3");

    cout << b << endl;

    b.place(Pawn::BLACK, "f4");

    cout << b << endl;

    b.place(Pawn::WHITE, "c5");

    cout << b << endl;

    b.place(Pawn::BLACK, "f4");

    cout << b << endl;

    b.place(Pawn::BLACK, "f4");

    cout << b << endl;

    return 0;
}