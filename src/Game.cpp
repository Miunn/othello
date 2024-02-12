#include <iostream>
#include <string>
#include <vector>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"

Game::Game()
{
    this->b = new Board;
    this->currentPlayer = Pawn::BLACK;
    this->runningGame = false;
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
    // Change the player
    this->currentPlayer = this->currentPlayer == Pawn::BLACK ? Pawn::WHITE : Pawn::BLACK;

    if (b->getValidMoves(currentPlayer).size() != 0)
    {
        return; // No problem
    }

    // No moves for next player
    // Skip his turn
    this->currentPlayer = this->currentPlayer == Pawn::BLACK ? Pawn::WHITE : Pawn::BLACK;

    if (b->getValidMoves(currentPlayer).size() != 0)
    {
        return; // No problem
    }

    // Game finished
    this->runningGame = false;

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
    std::string playedCoord;
    this->runningGame = true;
    do
    {
        std::cout << *b << std::endl;
        b->printValidMoves(b->getValidMoves(currentPlayer));
        playedCoord = readAndPlayFromSTDin();
    } while (runningGame && !b->isGameFinished() && playedCoord != "");
}