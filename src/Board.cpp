#include <iostream>
#include <string>
#include "../includes/Board.h"

using namespace std;

/**
 * @brief Display the board
 * 
 * @param out Outstream
 * @param B Board to display
 * @return ostream& 
 */
ostream &operator<<(ostream &out, const Board &B)
{
    for (int i = 0; i < B.size; i++) {
        for (int j = 0; j < B.size; j++) {
            if (B.board[i*B.size + j] == Pawn::BLACK) {
                out << '#';
            } else if (B.board[i*B.size + j] == Pawn::WHITE) {
                out << 'O';
            } else {
                out << '.';
            }
            out << ' ';
        }
        out << endl;
    }
    return out;
}

/**
 * @brief Construct a new Board object
 * 
 */
Board::Board()
{
    size = 8;
    board = (Pawn*) calloc(size * size, sizeof(Pawn));

    setCoord(Pawn::WHITE, "d4");
    setCoord(Pawn::WHITE, "e5");
    setCoord(Pawn::BLACK, "d5");
    setCoord(Pawn::BLACK, "e4");
}

/**
 * @brief Destroy the Board object
 * 
 */
Board::~Board()
{
    free(board);
}

/**
 * @brief Set pawn at coordinates
 * 
 * @param color Pawn to set
 * @param coord Pawn's coordinates
 */
void Board::setCoord(const Pawn& color, const string& coord) {
    board[((int)(coord[1]-'1')) * size + ((int)coord[0]-'a')] = color;
}

/**
 * @brief Return Pawn at coordinates coords
 * 
 * @param coord Pawn's coordinate to return ("a1")
 * @return Pawn 
 */
Pawn Board::getCoord(const string& coord) const {
    return board[((int)(coord[1]-'1')) * size + ((int)coord[0]-'a')];
}