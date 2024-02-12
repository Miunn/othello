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

std::string Game::readAndPlayFromSTDin()
{
    std::string coord;

    std::cout << (currentPlayer == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << " > ";
    std::cin >> coord;

    if (this->b->play(currentPlayer, coord))
    {
        togglePlayer();
        return coord;
    }
    return "";
}

void Game::startGame()
{
    std::string playedCoord = "aa";
    while (!b->isGameFinished() && playedCoord != "")
    {
        std::cout << *b << std::endl;
        b->printValidMoves(b->getValidMove(currentPlayer));
        playedCoord = readAndPlayFromSTDin();
        std::cout << "Played: " << playedCoord << std::endl;
    }
}