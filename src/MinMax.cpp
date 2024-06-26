#include <iostream>
#include <bits/stdc++.h> 
#include "../includes/MinMax.hpp"

MinMax::MinMax(int depth, Strategy strategy)
{
    this->player = Pawn::BLACK;
    this->ennemy = Pawn::WHITE;
    this->depth = depth;
    this->strategy = strategy;
}

MinMax::MinMax(Pawn player, int depth, Strategy strategy)
{
    this->player = player;

    if (this->player == Pawn::BLACK)
    {
        this->ennemy = Pawn::WHITE;
    }
    else
    {
        this->ennemy = Pawn::BLACK;
    }

    this->depth = depth;
    this->strategy = strategy;
}

int MinMax::heuristic(const Board &B, std::string move) const
{
    switch (this->strategy)
    {
    case POSITIONNEL:
        return heuristic_pos(B);
    
    case ABSOLU:
        return heuristic_abs(B);

    case MOBILITE:
        return heuristic_mob(B, move);

    case MIXTE:
        return heuristic_mixte(B, move);

    default:
        return -1;
    }
}

int MinMax::heuristic_pos(const Board &B) const
{
    int score = 0;
    for (int i = 0; i < B.getSize(); i++)
    {
        for (int j = 0; j < B.getSize(); j++)
        {
            int c = i * B.getSize() + j;
            if (B.getCoord(c) == this->player)
            {
                score += this->payoff_matrix[c];
            }
        }
    }
    return score;
}

int MinMax::heuristic_abs(const Board &B) const
{
    // Care to the sign for the operation
    if (this->player == Pawn::BLACK)
    {
        return B.getBlackScore() - B.getWhiteScore();
    }
    else
    {
        return B.getWhiteScore() - B.getBlackScore();
    }
}

int MinMax::heuristic_mob(const Board &B, std::string move) const
{
    if (this->payoff_matrix[B.coordToIndex(move)] > 400)
    {
        return this->payoff_matrix[B.coordToIndex(move)];
    }

    if (B.getCurrentPlayer() == Pawn::BLACK)
    {
        return B.getValidMoves(B.getCurrentPlayer()).size() - B.getValidMoves(Pawn::WHITE).size();
    }

    return B.getValidMoves(B.getCurrentPlayer()).size() - B.getValidMoves(Pawn::BLACK).size();
}

int MinMax::heuristic_mixte(const Board &B, std::string move) const
{
    if (B.getMovesPlayed() < 25)
    {
        return this->heuristic_pos(B);
    }
    else if (B.getMovesPlayed() < 42)
    {
        return this->heuristic_mob(B, move);
    }

    return this->heuristic_abs(B);
}

std::string MinMax::play(const Board &board) const
{
    std::vector<std::string> moves = board.getValidMoves(this->player);
    std::vector<int> scores = {};
    for (int i = 0; i < (int) moves.size(); i++)
    {
        Board *copy_board = new Board(board);
        copy_board->play(moves[i]);
        scores.push_back(play_research(*copy_board, moves.at(i), 1, board.getCurrentPlayer()));
        delete copy_board;
    }

    int max_index = 0;
    for (int i = 1; i < (int) scores.size(); i++)
    {
        if (scores.at(i) > scores.at(max_index))
        {
            max_index = i;
        }
    }

    return moves.at(max_index);
}

int MinMax::play_research(const Board &board, std::string move, int depth, Pawn maxPawn) const
{
    if (this->depth == depth)
    {
        return this->heuristic(board, move);
    }


    std::vector<Board*> sub_boards;
    std::vector<std::string> moves = board.getValidMoves(board.getCurrentPlayer());
    for (int j = 0; j < (int)moves.size(); j++)
    {
        Board *copy_board = new Board(board);
        copy_board->play(moves.at(j));
        sub_boards.push_back(copy_board);
    }
    
    // Pas de sous-plateau, on a donc une partie terminée
    // Soit gagnée, soit perdue
    // On retourne arbitrairement +inf lors d'une victoire
    // -inf lors d'une défaite
    // Et l'heuristique lors d'un match nul
    if (sub_boards.size() == 0 && board.getBlackScore() > board.getWhiteScore() && this->player == Pawn::BLACK)
    {
        return INT32_MAX;
    }
    else if (sub_boards.size() == 0 && board.getWhiteScore() > board.getBlackScore() && this->player == Pawn::WHITE)
    {
        return INT32_MAX;
    }
    else if (sub_boards.size() == 0 && board.getBlackScore() == board.getWhiteScore())
    {
        return this->heuristic(board, move);
    }
    else if (sub_boards.size() == 0)
    {
        return INT32_MIN;
    }

    std::vector<int> scores = {};

    for (int i = 0; i < (int)sub_boards.size(); i++)
    {
        scores.push_back(this->play_research(*sub_boards.at(i), moves.at(i), depth+1, maxPawn));
        delete sub_boards.at(i);
    }

    if (board.getCurrentPlayer() == maxPawn)
    {
        return (int) *std::max_element(scores.begin(), scores.end());
    }
    else
    {
        return (int) *std::min_element(scores.begin(), scores.end());
    }
}