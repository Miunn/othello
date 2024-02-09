#ifndef BOARD_H
#define BOARD_H
#include <vector>

/**
 * @brief Represent a Pawn in a Board
 *
 */
typedef enum : unsigned short
{
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
} Pawn;

typedef enum : unsigned short
{
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
    friend std::ostream &operator<<(std::ostream &, const Board &P);

public:
    Board();
    ~Board();
    bool isValidCoord(const int& coord) const;
    void setCoord(const Pawn& color, const int& coord);
    Pawn getCoord(const int& coord) const;
    bool canBePlaced(const Pawn& pawn, const int& coord) const;
    bool place(const Pawn& pawn, const int& coord);
    bool play(const Pawn& pawn, const std::string& coord);
    Direction getValidDirection(const Pawn& pawn, const int& coord) const;
    void switchPawns(const Pawn& placedPawn, const int& sourceCoord, Direction direction);
    void switchPawnsTop(const Pawn &placedPawn, const int& sourceCoord);
    void switchPawnsRight(const Pawn &placedPawn, const int& sourceCoord);
    void switchPawnsBottom(const Pawn &placedPawn, const int& sourceCoord);
    void switchPawnsLeft(const Pawn &placedPawn, const int& sourceCoord);
    void switchPawnsDTR(const Pawn  &placedPawn, const int& sourceCoord);
    void switchPawnsDBR(const Pawn  &placedPawn, const int& sourceCoord);
    void switchPawnsDBL(const Pawn  &placedPawn, const int& sourceCoord);
    void switchPawnsDTL(const Pawn  &placedPawn, const int& sourceCoord);
    bool* getValidMove(const Pawn &pawn) const;

    int coordToIndex(const std::string& coord) const;
    std::string indexToCoord(const int& index) const;

    bool isGameFinished() const;

private:
    int size;
    Pawn *board;
};

#endif