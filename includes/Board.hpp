#ifndef BOARD_H
#define BOARD_H
#include <vector>

/**
 * @brief Represent a Pawn in a Board
 * 
 */
typedef enum: unsigned short
{
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
} Pawn;

typedef enum: unsigned short
{
    NONE = 0,
    TOP = 1,
    RIGHT = 2,
    BOTTOM = 4,
    LEFT = 8,
    DTR = 16,
    DBR = 32,
    DBL = 64,
    DTL = 128,
} Direction;

/**
 * @brief Othello board game
 * 
 */
class Board
{
    // Surcharge the operator '<<'
    friend std::ostream & operator<<(std::ostream &, const Board &P); 

    public: 
    Board();
    ~Board();
    bool isValidCoord(const std::string& coord) const;
    void setCoord(const Pawn& color, const std::string& coord);
    Pawn getCoord(const std::string& coord) const;
    bool canBePlaced(const std::string& coord) const;
    bool place(const Pawn& pawn, const std::string& coord);
    Direction getValidDirection(const Pawn& pawn, const std::string& coord) const;
    std::vector<std::string> getValidMove(const Pawn &pawn) const;

    private:
    int size;
    Pawn *board;

};

#endif