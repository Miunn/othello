#include <iostream>
#include "../includes/Board.h"
#include "../includes/Pawn.h"

using namespace std;

ostream &operator<<(ostream &out, const Board &B)
{
    for (int i = 0; i < B.size; i++) {
        for (int j = 0; j < B.size; j++) {
            out << B.board[i*B.size + j]->getColor() << " ";
        }
        out << endl;
    }
    return out;
}

Board::Board()
{
    size = 8;
    board = (Pawn**) malloc(size * size * sizeof(Pawn*));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i*size + j] = new Pawn();
        }
    }

    setPawnAtCord(1, 'd', 4);
    setPawnAtCord(1, 'e', 5);
    setPawnAtCord(2, 'd', 5);
    setPawnAtCord(2, 'e', 4);
}

Board::~Board()
{
    free(board);
}

void Board::setPawnAtCord(int color, char col, int row) {
    board[(row-1) * size + col-97]->setCoords(col, row);
    board[(row-1) * size + col-97]->setColor(color);
}