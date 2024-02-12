#include <iostream>
#include <string>
#include <vector>
#include "../includes/Board.hpp"

using namespace std;

/**
 * @brief Re-define binary operation to set direction flags
 *
 * @param a First direction
 * @param b Second direction
 * @return Direction
 */
inline Direction operator|(Direction a, Direction b)
{
    return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
}

/**
 * @brief Display the board
 *
 * @param out Outstream
 * @param B Board to display
 * @return ostream&
 */
ostream &operator<<(ostream &out, const Board &B)
{
    out << "  a b c d e f g h" << endl;
    for (int i = 0; i < B.size; i++)
    {
        out << i + 1 << " ";
        for (int j = 0; j < B.size; j++)
        {
            if (B.board[i * B.size + j] == Pawn::BLACK)
            {
                out << '#';
            }
            else if (B.board[i * B.size + j] == Pawn::WHITE)
            {
                out << 'O';
            }
            else
            {
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
    board = (Pawn *)calloc(size * size, sizeof(Pawn));

    setCoord(Pawn::WHITE, coordToIndex("d4"));
    setCoord(Pawn::WHITE, coordToIndex("e5"));
    setCoord(Pawn::BLACK, coordToIndex("d5"));
    setCoord(Pawn::BLACK, coordToIndex("e4"));
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
 * @brief Check if the coord given is valid for othello gmae
 *
 * @param coord Coordinate to check
 * @return true If the coordinate is valid ("e4")
 * @return false If the coordinate is invalid ("z0")
 */
bool Board::isValidCoord(const int &coord) const
{
    return coord >= 0 && coord < 64;
}

/**
 * @brief Set pawn at coordinates
 *
 * @param color Pawn to set
 * @param coord Pawn's coordinates
 */
void Board::setCoord(const Pawn &color, const int &coord)
{
    if (!isValidCoord(coord))
        return;
    board[coord] = color;
}

/**
 * @brief Return Pawn at coordinates coords
 *
 * @param coord Pawn's coordinate to return ("a1")
 * @return Pawn
 */
Pawn Board::getCoord(const int &coord) const
{
    if (!isValidCoord(coord))
        throw -1;
    return board[coord];
}

int Board::coordToIndex(const string &coord) const
{
    return (coord[1] - '1') * this->size + coord[0] - 'a';
}

string Board::indexToCoord(const int &index) const
{
    return string(1, 'a' + index % 8) + string(1, '1' + index / 8);
}

/**
 * @brief Check if a Pawn can be placed at a given coordinate
 * Doesn't check if it's a valid move (use getValidDirection for that)
 *
 * @param coord Coord to check
 * @return true If a Pawn can be placed
 * @return false If the coord isn't empty
 */
bool Board::canBePlaced(const Pawn &pawn, const int &coord) const
{
    return isValidCoord(coord) && getCoord(coord) == Pawn::EMPTY;
}

Direction Board::getValidDirection(const Pawn &pawn, const int &coord) const
{
    if (!isValidCoord(coord))
        return Direction::NONE;

    Direction validDirection = Direction::NONE;

    // Top
    for (int row = coord - 8; row >= 0; row -= size)
    {
        Pawn currentPawn = getCoord(row);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord - row > 8)
        {
            validDirection = validDirection | Direction::TOP;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Bottom
    for (int row = coord + 8; row < 64; row += 8)
    {
        Pawn currentPawn = getCoord(row);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && row - coord > 8)
        {
            validDirection = validDirection | Direction::BOTTOM;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Left
    for (int col = coord - 1; col > coord - coord % 8; col--)
    {
        Pawn currentPawn = getCoord(col);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord - col > 1)
        {
            validDirection = validDirection | Direction::LEFT;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Right
    for (int col = coord + 1; col < coord + 8 - (coord % 8); col++)
    {
        Pawn currentPawn = getCoord(col);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && col - coord > 1)
        {
            validDirection = validDirection | Direction::RIGHT;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal TOP RIGHT
    for (int diag = coord - 7; diag > coord + 8 - (coord % 8) - (7 - coord % 8) * 8 && diag >= 0; diag -= 7)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord - diag > 7)
        {
            validDirection = validDirection | Direction::DTR;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal BOTTOM RIGHT
    for (int diag = coord + 9; diag < coord + 8 - (coord % 8) + (7 - coord % 8) * 8 && diag < 64; diag += 9)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && diag - coord > 9)
        {
            validDirection = validDirection | Direction::DBR;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal BOTTOM LEFT
    for (int diag = coord + 7; diag < coord - (coord % 8) + coord % 8 * 8 && diag < 64; diag += 7)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && diag - coord > 7)
        {
            validDirection = validDirection | Direction::DBL;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal TOP LEFT
    for (int diag = coord - 9; diag >= coord - (coord % 8) - coord % 8 * 8 && diag >= 0; diag -= 9)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord - diag > 9)
        {
            validDirection = validDirection | Direction::DTL;
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    return validDirection;
}

void Board::switchPawns(const Pawn &placedPawn, const int &sourceCoord, Direction direction)
{
    if (direction & Direction::TOP)
        switchPawnsTop(placedPawn, sourceCoord);
    if (direction & Direction::RIGHT)
        switchPawnsRight(placedPawn, sourceCoord);
    if (direction & Direction::BOTTOM)
        switchPawnsBottom(placedPawn, sourceCoord);
    if (direction & Direction::LEFT)
        switchPawnsLeft(placedPawn, sourceCoord);
    if (direction & Direction::DTR)
        switchPawnsDTR(placedPawn, sourceCoord);
    if (direction & Direction::DBR)
        switchPawnsDBR(placedPawn, sourceCoord);
    if (direction & Direction::DBL)
        switchPawnsDBL(placedPawn, sourceCoord);
    if (direction & Direction::DTL)
        switchPawnsDTL(placedPawn, sourceCoord);
}

void Board::switchPawnsTop(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int row = sourceCoord - 8; row >= 0; row -= size)
    {
        Pawn currentPawn = getCoord(row);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, row);
    }
}

void Board::switchPawnsRight(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int col = sourceCoord + 1; col <= sourceCoord + 8 - (sourceCoord % 8); col++)
    {
        Pawn currentPawn = getCoord(col);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, col);
    }
}

void Board::switchPawnsBottom(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int row = sourceCoord + 8; row < 64; row += 8)
    {
        Pawn currentPawn = getCoord(row);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, row);
    }
}

void Board::switchPawnsLeft(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int col = sourceCoord - 1; col > sourceCoord - sourceCoord % 8; col--)
    {
        Pawn currentPawn = getCoord(col);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, col);
    }
}

void Board::switchPawnsDTR(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int diag = sourceCoord - 7; diag > sourceCoord + 8 - (sourceCoord % 8) - (7 - sourceCoord % 8) * 8 && diag >= 0; diag -= 7)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, diag);
    }
}

void Board::switchPawnsDBR(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int diag = sourceCoord + 9; diag < sourceCoord + 8 - (sourceCoord % 8) + (7 - sourceCoord % 8) * 8 && diag < 64; diag += 9)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, diag);
    }
}

void Board::switchPawnsDBL(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int diag = sourceCoord + 7; diag < sourceCoord - (sourceCoord % 8) + sourceCoord % 8 * 8 && diag < 64; diag += 7)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, diag);
    }
}

void Board::switchPawnsDTL(const Pawn &placedPawn, const int &sourceCoord)
{
    for (int diag = sourceCoord - 9; diag >= sourceCoord - (sourceCoord % 8) - sourceCoord % 8 * 8 && diag >= 0; diag -= 9)
    {
        Pawn currentPawn = getCoord(diag);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, diag);
    }
}

bool *Board::getValidMove(const Pawn &pawn) const
{
    bool *validCoords = (bool *)calloc(64, sizeof(bool));

    for (int coord = 0; coord < 64; coord++)
    {
        if (canBePlaced(pawn, coord) && getValidDirection(pawn, coord) != 0)
        {
            validCoords[coord] = true;
        }
    }

    return validCoords;
}

void Board::printValidMoves(bool* moves) const
{
    for (int i = 0; i < size*size; i++)
    {
        if (moves[i])
        {
            cout << (char)('a' + i%8) << (char)('1' + i/8) << " ";
        }
    }
    cout << endl;
}

bool Board::place(const Pawn &pawn, const int &coord)
{
    if (!canBePlaced(pawn, coord))
        return false;

    setCoord(pawn, coord);

    return true;
}

bool Board::isGameFinished() const
{
    return getValidMove(Pawn::BLACK) == 0 && getValidMove(Pawn::WHITE);
}

bool Board::play(const Pawn &pawn, const std::string &coord)
{
    int indexCoord = coordToIndex(coord);

    if (!isValidCoord(indexCoord))
        return false;

    Direction moveDirection = getValidDirection(pawn, indexCoord);

    if (moveDirection == 0)
        return false; // Illegal move

    if (isGameFinished())
        return false; // Game is finished

    if (!place(pawn, indexCoord))
        return false;

    switchPawns(pawn, indexCoord, moveDirection);

    return true;
}