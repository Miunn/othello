#include <iostream>
#include "../includes/Player.hpp"

Player::Player()
{
    this->player = Pawn::BLACK;
}

Player::Player(Pawn player)
{
    this->player = player;
}

std::string Player::play(const Board& board) const
{
    std::string coord;

    std::cout << board << std::endl;
    board.printValidMoves(board.getValidMoves(this->player));
    std::cout << (this->player == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << " > ";
    std::cin >> coord;

    if (coord.compare("quit") == 0)
    {
        std::cout << "Quit" << std::endl;
        return "";
    }

    if (!board.canBePlaced(this->player, board.coordToIndex(coord)) || (board.getValidDirection(this->player, board.coordToIndex(coord)) & Direction::NONE))
    {
        std::cout << "Invalid coord" << std::endl;
        return this->play(board);
    }

    return coord;
}