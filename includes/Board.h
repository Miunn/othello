#ifndef BOARD_H
#define BOARD_H

typedef enum: unsigned short
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
    void setCoord(const Pawn& color, const std::string& coord);
    Pawn getCoord(const std::string& coord) const;
        
    private:
    int size;
    Pawn *board;

};

#endif