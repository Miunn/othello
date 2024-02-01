#ifndef BOARD_H
#define BOARD_H
#include "Pawn.h"

class Board
{
friend std::ostream & operator<<(std::ostream &, const Board &P); 

    public: 
    Board();
    ~Board();
    void setPawnAtCord(int color, char col, int row);
        
    private:
    int size;
    Pawn **board;

};

#endif