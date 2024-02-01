#include <iostream>
#include "../includes/Board.h"

using namespace std;

ostream &operator<<(ostream &out, const Board &B)
{
    for (int i = 0; i < B.size; i++) {
        for (int j = 0; j < B.size; j++) {
            out << B.board[i*B.size + j] << " ";
        }
        out << endl;
    }
    return out;
}

Board::Board()
{
    size = 8;
    board = (int*) calloc(size * size, sizeof(int));

    setPawnAtCord(Pawn::WHITE, 'd', 4);
    setPawnAtCord(Pawn::WHITE, 'e', 5);
    setPawnAtCord(Pawn::BLACK, 'd', 5);
    setPawnAtCord(Pawn::BLACK, 'e', 4);
}

Board::~Board()
{
    free(board);
}

void Board::setPawnAtCord(Pawn color, char col, int row) {
    board[(row-1) * size + col-97] = color;
}