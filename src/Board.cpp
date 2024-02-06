#include <iostream>
#include <string>
#include <vector>
#include "../includes/Board.hpp"

using namespace std;

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

    /*setCoord(Pawn::WHITE, "d4");
    setCoord(Pawn::WHITE, "e5");
    setCoord(Pawn::BLACK, "d5");
    setCoord(Pawn::BLACK, "e4");*/
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
bool Board::isValidCoord(const string &coord) const
{
    if (coord[0] < 'a' || coord[0] > 'h')
        return false;
    if (coord[1] < '1' || coord[1] > '8')
        return false;
    return coord[2] == '\0';
}

/**
 * @brief Set pawn at coordinates
 *
 * @param color Pawn to set
 * @param coord Pawn's coordinates
 */
void Board::setCoord(const Pawn &color, const string &coord)
{
    board[((int)(coord[1] - '1')) * size + ((int)coord[0] - 'a')] = color;
}

/**
 * @brief Return Pawn at coordinates coords
 *
 * @param coord Pawn's coordinate to return ("a1")
 * @return Pawn
 */
Pawn Board::getCoord(const string &coord) const
{
    return board[((int)(coord[1] - '1')) * size + ((int)coord[0] - 'a')];
}

/**
 * @brief Check if a Pawn can be placed at a given coordinate
 * Doesn't check if it's a valid move (use getValidDirection for that)
 *
 * @param coord Coord to check
 * @return true If a Pawn can be placed
 * @return false If the coord isn't empty
 */
bool Board::canBePlaced(const Pawn& pawn, const string &coord) const
{
    if (!isValidCoord(coord) || getCoord(coord) != Pawn::EMPTY)
    {
        return false;
    }

    return true;
}

vector<Direction> Board::getValidDirection(const Pawn &pawn, const std::string &coord) const
{
    if (!isValidCoord(coord))
        return {};

    vector<Direction> validDirection = {};

    // Top
    for (char row = coord[1] - 1; row >= '1'; row--)
    {
        Pawn currentPawn = getCoord(string(1, coord[0]) + string(1, row));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord[1] - row > 1)
        {
            validDirection.push_back(Direction::TOP);
            break;
        }
        else if (currentPawn == pawn && coord[1] - row <= 1)
        {
            break;
        }
    }

    // Bottom
    for (char row = coord[1] + 1; row <= '8'; row++)
    {
        Pawn currentPawn = getCoord(string(1, coord[0]) + string(1, row));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && row - coord[1] > 1)
        {
            validDirection.push_back(Direction::BOTTOM);
            break;
        }
        else if (currentPawn == pawn && row - coord[1] <= 1)
        {
            break;
        }
    }

    // Left
    for (char col = coord[0] - 1; col >= 'a'; col--)
    {
        Pawn currentPawn = getCoord(string(1, col) + string(1, coord[1]));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord[0] - col > 1)
        {
            validDirection.push_back(Direction::LEFT);
            break;
        }
        else if (currentPawn == pawn && coord[0] - col <= 1)
        {
            break;
        }
    }

    // Right
    for (char col = coord[0] + 1; col <= 'h'; col++)
    {
        Pawn currentPawn = getCoord(string(1, col) + string(1, coord[1]));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && col - coord[0] > 1)
        {
            validDirection.push_back(Direction::RIGHT);
            break;
        }
        else if (currentPawn == pawn && col - coord[0] <= 1)
        {
            break;
        }
    }

    // Diagonal TOP RIGHT
    for (char col = coord[0] + 1, row = coord[1] - 1; col <= 'h' && row >= '1'; col++, row--)
    {
        Pawn currentPawn = getCoord(string(1, col) + string(1, row));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && col - coord[0] > 1 && coord[1] - row > 1)
        {
            validDirection.push_back(Direction::DTR);
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal BOTTOM RIGHT
    for (char col = coord[0] + 1, row = coord[1] + 1; col <= 'h' && row <= '8'; col++, row++)
    {
        Pawn currentPawn = getCoord(string(1, col) + string(1, row));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && col - coord[0] > 1 && row - coord[1] > 1)
        {
            validDirection.push_back(Direction::DBR);
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal BOTTOM LEFT
    for (char col = coord[0] - 1, row = coord[1] + 1; col >= 'a' && row <= '8'; col--, row++)
    {
        Pawn currentPawn = getCoord(string(1, col) + string(1, row));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord[0] - col > 1 && row - coord[1] > 1)
        {
            validDirection.push_back(Direction::DBL);
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    // Diagonal TOP LEFT
    for (char col = coord[0] - 1, row = coord[1] - 1; col >= 'a' && row >= '1'; col--, row--)
    {
        Pawn currentPawn = getCoord(string(1, col) + string(1, row));

        if (currentPawn == Pawn::EMPTY)
        {
            break;
        }

        if (currentPawn == pawn && coord[0] - col > 1 && coord[1] - row > 1)
        {
            validDirection.push_back(Direction::DTL);
            break;
        }
        else if (currentPawn == pawn)
        {
            break;
        }
    }

    return validDirection;
}

void Board::switchPawns(const Pawn& placedPawn, const std::string& sourceCoord, Direction direction)
{
    switch (direction)
    {
    case TOP:
        switchPawnsTop(placedPawn, sourceCoord);
        break;
    
    case RIGHT:
        switchPawnsRight(placedPawn, sourceCoord);
        break;

    case BOTTOM:
        switchPawnsBottom(placedPawn, sourceCoord);
        break;

    case LEFT:
        switchPawnsLeft(placedPawn, sourceCoord);
        break;
    
    case DTR:
        switchPawnsDTR(placedPawn, sourceCoord);
        break;

    case DBR:
        switchPawnsDBR(placedPawn, sourceCoord);
        break;

    case DBL:
        switchPawnsDBL(placedPawn, sourceCoord);
        break;

    case DTL:
        switchPawnsDTL(placedPawn, sourceCoord);
        break;

    default:
        break;
    }
    
}

void Board::switchPawnsTop(const Pawn &placedPawn, const std::string& sourceCoord)
{
    for (char row = sourceCoord[1] - 1; row >= '1'; row--)
    {
        string currCoord = string(1, sourceCoord[0]) + string(1, row);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }
        
        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsRight(const Pawn &placedPawn, const std::string& sourceCoord)
{
    for (char col = sourceCoord[0] + 1; col <= 'h'; col++)
    {
        string currCoord = string(1, col) + string(1, sourceCoord[1]);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }
        
        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsBottom(const Pawn &placedPawn, const std::string& sourceCoord)
{
    for (char row = sourceCoord[1] + 1; row <= '8'; row++)
    {
        string currCoord = string(1, sourceCoord[0]) + string(1, row);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }
        
        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsLeft(const Pawn &placedPawn, const std::string& sourceCoord)
{
    for (char col = sourceCoord[0] - 1; col >= 'a'; col--)
    {
        string currCoord = string(1, col) + string(1, sourceCoord[1]);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsDTR(const Pawn  &placedPawn, const std::string& sourceCoord)
{
    for (char col = sourceCoord[0] + 1, row = sourceCoord[1] - 1; col <= 'h' && row >= '1'; col++, row--)
    {
        string currCoord = string(1, col) + string(1, row);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsDBR(const Pawn  &placedPawn, const std::string& sourceCoord)
{
    for (char col = sourceCoord[0] + 1, row = sourceCoord[1] + 1; col <= 'h' && row <= '8'; col++, row++)
    {
        string currCoord = string(1, col) + string(1, row);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsDBL(const Pawn  &placedPawn, const std::string& sourceCoord)
{
    for (char col = sourceCoord[0] - 1, row = sourceCoord[1] + 1; col >= 'a' && row <= '8'; col--, row++)
    {
        string currCoord = string(1, col) + string(1, row);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, currCoord);
    }
}

void Board::switchPawnsDTL(const Pawn  &placedPawn, const std::string& sourceCoord)
{
    for (char col = sourceCoord[0] - 1, row = sourceCoord[1] - 1; col >= 'a' && row >= '1'; col--, row--)
    {
        string currCoord = string(1, col) + string(1, row);
        Pawn currentPawn = getCoord(currCoord);

        if (currentPawn == Pawn::EMPTY || currentPawn == placedPawn)
        {
            break;
        }

        setCoord(placedPawn, currCoord);
    }
}

vector<string> Board::getValidMove(const Pawn &pawn) const
{
    vector<string> validCoords = {};

    for (char r = '1'; r <= '8'; r++)
    {
        for (char c = 'a'; c <= 'h'; c++)
        {
            string currCoord = string(1, c) + string(1, r);
            if (canBePlaced(pawn, currCoord) && getValidDirection(pawn, string(1, c) + string(1, r)).size() > 0)
            {
                validCoords.push_back(currCoord);
            }
        }
    }

    return validCoords;
}

bool Board::place(const Pawn &pawn, const std::string &coord)
{
    if (!canBePlaced(pawn, coord))
    {
        return false;
    }

    setCoord(pawn, coord);

    return true;
}

bool Board::play(const Pawn &pawn, const std::string& coord)
{
    if (!isValidCoord(coord)) return false;

    vector<Direction> moveDirection = getValidDirection(pawn, coord);
    
    if (moveDirection.size() == 0) return false;    // Illegal move
    if (!place(pawn, coord)) return false;
    
    for (int i = 0; i < (int) moveDirection.size(); i++)
    {
        switchPawns(pawn, coord, moveDirection[i]);
    }
    return true;
}