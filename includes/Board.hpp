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
    friend std::ostream &operator<<(std::ostream &, const Board &P);

public:
    /**
     * @brief Construct a new Board object 
     * by initializing a 8x8 board
     * 
     */
    Board();

    /**
     * @brief Destroy the Board object
     * 
     */
    ~Board();

    /**
     * @brief Check if a given index-coordinate if a valid board coord
     * 
     * @param coord Coordinate to check
     * @return true If the coordinate is valid
     * @return false If the coordinate is invalid
     */
    bool isValidCoord(const int& coord) const;

    /**
     * @brief Set the pawn at a given coordinate
     * No check are made except isValidCoord
     * 
     * @param color Pawn to place
     * @param coord Coordinate where to place the pawn
     */
    void setCoord(const Pawn& color, const int& coord);

    /**
     * @brief Get the Pawn at a given coordinate
     * 
     * @param coord Coordinate to retreive
     * @return Pawn Pawn on the board
     */
    Pawn getCoord(const int& coord) const;

    /**
     * @brief Check if a Pawn can be placed at a given coordinate
     * 
     * @param pawn Pawn to place
     * @param coord Coordinate where to place the Pawn
     * @return true If coordinate is valid and no Pawns are placed
     * @return false If not
     */
    bool canBePlaced(const Pawn& pawn, const int& coord) const;

    /**
     * @brief Check if a Pawn can be placed at a given coordinate and place it
     * This doesn't check if the move is valid
     * 
     * @param pawn Pawn to place
     * @param coord Coordinate where to place the pawn
     * @return true If the pawn has been placed
     * @return false If the pawn hasn't been place
     */
    bool place(const Pawn& pawn, const int& coord);

    /**
     * @brief Play a valid move at a given coordinate
     * 
     * @param pawn Pawn to place
     * @param coord Cooordinate where to place the pawn
     * @return true If the move could have been made
     * @return false If the move is illegal
     */
    bool play(const Pawn& pawn, const std::string& coord);

    /**
     * @brief Get all valid direction for a pawn at a given coordinate
     * A valid direction is a direction where there is only ennemy pawn between the given coordinate and a self pawn at the other side
     * 
     * @param pawn Pawn to compute directions
     * @param coord Coodinate to check
     * @return Direction Binary mask with 1 for a valid direction. Use the Direction enum to test
     */
    Direction getValidDirection(const Pawn& pawn, const int& coord) const;

    /**
     * @brief Switch every ennemy pawn for a source coordinate and a direction
     * 
     * @param placedPawn Switched pawn color
     * @param sourceCoord Source coordinate
     * @param direction Direction to switch
     */
    void switchPawns(const Pawn& placedPawn, const int& sourceCoord, Direction direction);

    /**
     * @brief Sub function to switchpawns to switch every pawn for TOP direction at a coodinate
     * 
     * @param placedPawn Switched pawn color
     * @param sourceCoord Source coordinate
     */
    void switchPawnsTop(const Pawn &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for RIGHT direction at a coodinate
     * 
     * @param placedPawn Switched pawn color
     * @param sourceCoord Source coordinate
     */
    void switchPawnsRight(const Pawn &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for BOTTOM direction at a coodinate
     * 
     * @param placedPawn 
     * @param sourceCoord 
     */
    void switchPawnsBottom(const Pawn &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for LEFT direction at a coodinate
     * 
     * @param placedPawn 
     * @param sourceCoord 
     */
    void switchPawnsLeft(const Pawn &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for Top Right Diagonal direction at a coodinate
     * 
     * @param placedPawn 
     * @param sourceCoord 
     */
    void switchPawnsDTR(const Pawn  &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for Bottom Right Diagonal direction at a coodinate
     * 
     * @param placedPawn 
     * @param sourceCoord 
     */
    void switchPawnsDBR(const Pawn  &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for Bottom Left Diagonal direction at a coodinate
     * 
     * @param placedPawn 
     * @param sourceCoord 
     */
    void switchPawnsDBL(const Pawn  &placedPawn, const int& sourceCoord);

    /**
     * @brief Sub function to switchpawns to switch every pawn for Top Left Diagonal direction at a coodinate
     * 
     * @param placedPawn 
     * @param sourceCoord 
     */
    void switchPawnsDTL(const Pawn  &placedPawn, const int& sourceCoord);

    /**
     * @brief Get the all valid moves for a Pawn
     * 
     * @param pawn Pawn to compute moves
     * @return std::vector<std::string> Vector of all the possible moves
     */
    std::vector<std::string> getValidMoves(const Pawn &pawn) const;

    /**
     * @brief Print a valid moves vector
     * 
     * @param moves Valid moves' vector
     */
    void printValidMoves(std::vector<std::string> moves) const;

    /**
     * @brief Convert a string coordinate to index in the board
     * This doesn't check if the coordinate is valid
     * 
     * @param coord Coordinate to convert
     * @return int Index coordinate
     */
    int coordToIndex(const std::string& coord) const;

    /**
     * @brief Convert an index coordinate to a string coordinate
     * This doesn't check if the index is valid
     * 
     * @param index Index to convert
     * @return std::string String coordinate
     */
    std::string indexToCoord(const int& index) const;

    /**
     * @brief Tells if the game is finished (No moves available for both players)
     * 
     * @return true If the game is finished
     * @return false If the game can continue
     */
    bool isGameFinished() const;

private:
    /**
     * @brief Board size
     * 
     */
    int size;

    /**
     * @brief size*size array of Pawn representing the board
     * 
     */
    Pawn *board;
};

#endif