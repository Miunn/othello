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

Game::Game(Board *b, Pawn player)
{
    this->b = b;
    this->currentPlayer = player;
}

Game::~Game()
{
}

Board *Game::getBoard() const
{
    return this->b;
}

Pawn Game::getCurrentPlayer() const
{
    return this->currentPlayer;
}

std::vector<std::string> Game::togglePlayer()
{
    // Change the player
    this->currentPlayer = this->currentPlayer == Pawn::BLACK ? Pawn::WHITE : Pawn::BLACK;
    std::vector<std::string> moves = b->getValidMoves(currentPlayer);
    if (moves.size() != 0)
    {
        return moves; // No problem
    }

    // No moves for next player
    // Skip his turn
    std::cout << "Skip" << (currentPlayer == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << std::endl;
    this->currentPlayer = this->currentPlayer == Pawn::BLACK ? Pawn::WHITE : Pawn::BLACK;
    moves = b->getValidMoves(currentPlayer);
    if (moves.size() != 0)
    {
        return moves; // No problem
    }

    // Game finished
    this->runningGame = false;
    return {};
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
    std::cout << "Played false" << std::endl;
    return "";
}

void Game::startGame()
{
    std::string playedCoord = "aa";
    this->runningGame = true;

    if (b->isGameFinished())
    {
        std::cout << "Game already ended" << std::endl;
        std::cout << *b << std::endl;
        return;
    }

    std::vector<std::string> moves = {};

    std::cout << *b << std::endl;
    do
    {
        moves = b->getValidMoves(currentPlayer);

        if (moves.size() == 0)
        {
            std::cout << "Skip" << (currentPlayer == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << std::endl;
            if (togglePlayer().size() == 0)
            {
                break;
            }

            moves = b->getValidMoves(currentPlayer);
        }

        b->printValidMoves(moves);
        playedCoord = readAndPlayFromSTDin();
        std::cout << *b << std::endl;
    } while (runningGame && !b->isGameFinished() && playedCoord != "");
    std::cout << "Game ended" << std::endl;
    std::cout << *b << std::endl;
}