#include <iostream>
#include "../includes/Pawn.h"

using namespace std;

ostream &operator<<(ostream &out, const Pawn &P)
{
    out << P.color;
    return out;
}

Pawn::Pawn()
{
    color = 0;
    col = ' ';
    row = 0;
}

Pawn::Pawn(int color, char col, int row)
{
    this->color = color;
    this->col = col;
    this->row = row;
}

int Pawn::getColor() {
    return this->color;
}

void Pawn::setColor(int color) {
    this->color = color;
}

void Pawn::setCoords(char col, int row) {
    this->col = col;
    this->row = row;
}