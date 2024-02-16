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
    bool isValidCoord(const std::string &coord) const;
    void setCoord(const Pawn &color, const std::string &coord);
    Pawn getCoord(const std::string &coord) const;
    bool canBePlaced(const Pawn &pawn, const std::string &coord) const;
    bool place(const Pawn &pawn, const std::string &coord);
    bool gameFinished(const Pawn &pawn);
    int getScore(const Pawn &pawn) const;
    bool play(const Pawn &pawn, const std::string &coord);
    std::vector<Direction> getValidDirection(const Pawn &pawn, const std::string &coord) const;
    void switchPawns(const Pawn &placedPawn, const std::string &sourceCoord, Direction direction);
    void switchPawnsTop(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsRight(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsBottom(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsLeft(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsDTR(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsDBR(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsDBL(const Pawn &placedPawn, const std::string &sourceCoord);
    void switchPawnsDTL(const Pawn &placedPawn, const std::string &sourceCoord);
    std::vector<std::string> getValidMove(const Pawn &pawn) const;

private:
    int size;
    Pawn *board;
};

#endif