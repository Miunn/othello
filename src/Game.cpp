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
    this->runningGame = false;
}

Game::Game(Board *b, Pawn player)
{
    this->b = b;
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
    return this->getBoard()->getCurrentPlayer();
}

std::string Game::readAndPlayFromSTDin()
{
    std::string coord;

    std::cout << (this->getBoard()->getCurrentPlayer() == Pawn::BLACK ? "[BLACK]" : "[WHITE]") << " > ";
    std::cin >> coord;

    if (this->b->play(coord))
    {
        this->b->togglePlayer();
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

    std::vector<std::string> moves = b->getValidMoves(this->getBoard()->getCurrentPlayer());
    
    // Skip player on first turn if no move
    if (moves.size() == 0)
    {
        this->b->togglePlayer();
        moves = b->getValidMoves(this->getBoard()->getCurrentPlayer());
    }

    do
    {
        if (this->getBoard()->getCurrentPlayer() == Pawn::BLACK)
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

        if (this->b->play(playedCoord))
        {
            this->b->togglePlayer();
        }

        if (this->b->isGameFinished())
        {
            this->runningGame = false;
        }
        
    } while (runningGame && !b->isGameFinished() && playedCoord != "");
}

Pawn Game::analyseGame(bool verbose, bool displayGrid) const
{
    if (!this->b->isGameFinished())
    {
        std::cout << "Called analyse on an unfinished game" << std::endl;
        return Pawn::EMPTY;
    }

    Pawn winner;
    if (this->b->getBlackScore() > this->b->getWhiteScore())
    {
        winner = Pawn::BLACK;
    }
    else if (this->b->getWhiteScore() > this->b->getBlackScore())
    {
        winner = Pawn::WHITE;
    }
    else
    {
        winner = Pawn::EMPTY;
    }

    if (!verbose)
    {
        return winner;
    }


    std::cout << "+-----------------------+" << std::endl;
    std::cout << "| Résultat: ";
    if (winner == Pawn::BLACK)
    {
        std::cout << std::setw(13) << "Noirs |" << std::endl;
    }
    else if (winner == Pawn::WHITE)
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
    return winner;
}