#include <iostream>
#include <string>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"

Game::Game()
{
    this->b = new Board;
    this->currentPlayer = Pawn::BLACK;
}

Game::~Game()
{
    delete b;
}

Board* Game::getBoard() const
{
    return this->b;
}

Pawn Game::getCurrentPlayer() const
{
    return this->currentPlayer;
}

void Game::togglePlayer()
{
    this->currentPlayer = this->currentPlayer == Pawn::BLACK ? Pawn::WHITE : Pawn::BLACK;
}

void Game::readAndPlayFromSTDin()
{
    std::string coord;

    std::cout << (currentPlayer == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << " > ";
    std::cin >> coord;

    this->b->play(currentPlayer, coord);
    togglePlayer();
}