#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../includes/Board.hpp"
#include "../includes/Game.hpp"
#include "../includes/AInterface.hpp"

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

void Game::startGame(const AInterface &blackPlayer, const AInterface &whitePlayer)
{
    std::string playedCoord = "aa";
    this->runningGame = true;

    if (b->isGameFinished())
    {
        std::cout << "Game already ended" << std::endl;
        std::cout << *b << std::endl;
        return;
    }

    if (blackPlayer.getPlayer() == whitePlayer.getPlayer() || blackPlayer.getPlayer() != Pawn::BLACK || whitePlayer.getPlayer() != Pawn::WHITE)
    {
        std::cout << "Invalid player setup" << std::endl;
        return;
    }

    std::vector<std::string> moves = b->getValidMoves(currentPlayer);
    
    // Skip player on first turn if no move
    if (moves.size() == 0)
    {
        std::cout << "Skip" << (currentPlayer == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << std::endl;
        if (togglePlayer().size() == 0)
        {
            return;
        }

        moves = b->getValidMoves(currentPlayer);
    }

    std::cout << *b << std::endl;
    do
    {
        if (this->currentPlayer == Pawn::BLACK)
        {
            playedCoord = blackPlayer.play(*this->b);
        }
        else
        {
            playedCoord = whitePlayer.play(*this->b);
        }

        if (playedCoord.compare("") == 0)
        {
            this->runningGame = false;
            break;
        }

        if (this->b->play(currentPlayer, playedCoord))
        {
            moves = togglePlayer();
        }

        std::cout << *b << std::endl;

        if (moves.size() == 0)
        {
            this->runningGame = false;
        }
        
    } while (runningGame && !b->isGameFinished() && playedCoord != "");
    std::cout << "Game ended" << std::endl;
    std::cout << *b << std::endl;
}

void Game::analyseGame(bool displayGrid) const
{
    if (!this->b->isGameFinished())
    {
        std::cout << "Called analyse on an unfinished game" << std::endl;
        return;
    }

    std::cout << "+-----------------------+" << std::endl;
    std::cout << "| Résultat: ";
    if (this->b->getBlackScore() > this->b->getWhiteScore())
    {
        std::cout << std::setw(13) << "Noirs |" << std::endl;
    }
    else if (this->b->getWhiteScore())
    {
        std::cout << std::setw(13) << "Blancs |" << std::endl;
    }
    else
    {
        std::cout << std::setw(13) << "Egalité |" << std::endl;
    }
    std::cout << "|-----------------------|" << std::endl;
    std::cout << "| Vide | Noirs | Blancs |" << std::endl;
    std::cout << "|-----------------------|" << std::endl;
    std::cout << "|" << std::setw(5) << (this->b->getSize() * this->b->getSize() - this->b->getBlackScore() - this->b->getWhiteScore()) << " |" << std::setw(6) << this->b->getBlackScore() << " |" << std::setw(7) << this->b->getWhiteScore() << " |" << std::endl;
    std::cout << "+-----------------------+" << std::endl;

    if (displayGrid)
    {
        std::cout << "\nGrille de jeu:\n"
                  << *this->b << std::endl;
    }
}