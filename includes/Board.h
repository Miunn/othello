#ifndef BOARD_H
#define BOARD_H

typedef enum
{
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
} Pawn;

class Board
{
friend std::ostream & operator<<(std::ostream &, const Board &P); 

    public: 
    Board();
    ~Board();
    void setPawnAtCord(Pawn color, char col, int row);
        
    private:
    int size;
    int *board;

};

#endif