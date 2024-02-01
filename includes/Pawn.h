#ifndef PAWN_H
#define PAWN_H

class Pawn
{
friend std::ostream & operator<<(std::ostream &, const Pawn &P); 


    public: 
    Pawn();
    Pawn(int color, char col, int row);
    int getColor();
    void setColor(int color);
    void setCoords(char col, int row);

    private:
    int color;
    char col;
    int row;

};

#endif