#include <iostream>
#include <bits/stdc++.h>
#include "../includes/AlphaBeta.hpp"

AlphaBeta::AlphaBeta(int depth, Strategy strategy)
{
    this->player = Pawn::BLACK;
    this->ennemy = Pawn::WHITE;
    this->depth = depth;
    this->strategy = strategy;
}

AlphaBeta::AlphaBeta(Pawn player, int depth, Strategy strategy)
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

int AlphaBeta::heuristic(const Board &B, std::string move) const
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

int AlphaBeta::heuristic_pos(const Board &B) const
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

int AlphaBeta::heuristic_abs(const Board &B) const
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

int AlphaBeta::heuristic_mob(const Board &B, std::string move) const
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

int AlphaBeta::heuristic_mixte(const Board &B, std::string move) const
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

std::vector<Board *> AlphaBeta::computeSubBoards(const Board &board) const
{
    std::vector<Board *> depth_boards = {};
    std::vector<std::string> moves = board.getValidMoves(board.getCurrentPlayer());
    for (int j = 0; j < (int)moves.size(); j++)
    {
        Board *copy_board = new Board(board);
        copy_board->play(moves.at(j));
        depth_boards.push_back(copy_board);
    }
    return depth_boards;
}

std::string AlphaBeta::play(const Board &board) const
{
    std::vector<std::string> moves = board.getValidMoves(this->player);
    std::string best_move = moves.at(0);
    int maxEval = INT_MIN;
    for (int i = 0; i < (int)moves.size(); i++)
    {
        Board *copy_board = new Board(board);
        copy_board->play(moves.at(i));
        int eval = this->play_research(*copy_board, this->depth-1, INT_MIN, INT_MAX, this->player, moves.at(i));
        delete copy_board;
        if (eval > maxEval)
        {
            maxEval = eval;
            best_move = moves.at(i);
        }
    }
    return best_move;
}

int AlphaBeta::play_research(const Board &board, int depth, int alpha, int beta, Pawn maxPawn, std::string move) const
{
    if (depth == 0 || board.isGameFinished())
    {
        return this->heuristic(board, move);
    }

    std::vector<Board *> sub_boards = {};
    std::vector<std::string> moves = board.getValidMoves(board.getCurrentPlayer());
    for (int j = 0; j < (int)moves.size(); j++)
    {
        Board *copy_board = new Board(board);
        copy_board->play(moves.at(j));
        sub_boards.push_back(copy_board);
    }

    if (maxPawn == board.getCurrentPlayer())
    {
        int maxEval = INT_MIN;
        for (int i = 0; i < (int)sub_boards.size(); i++)
        {
            int eval = this->play_research(*sub_boards.at(i), depth - 1, alpha, beta, maxPawn, moves.at(i));
            maxEval = std::max(maxEval, eval);
            if (maxEval >= beta)
            {
                break;
            }
            alpha = std::max(alpha, eval);
        }

        for (int j = 0; j < (int)sub_boards.size(); j++)
        {
            delete sub_boards.at(j);
        }

        return maxEval;
    }
    else
    {
        int minEval = INT_MAX;
        for (int i = 0; i < (int)sub_boards.size(); i++)
        {
            int eval = this->play_research(*sub_boards.at(i), depth - 1, alpha, beta, maxPawn, moves.at(i));
            minEval = std::min(minEval, eval);
            if (minEval <= alpha)
            {
                break;
            }
            beta = std::min(beta, eval);
        }

        for (int j = 0; j < (int)sub_boards.size(); j++)
        {
            delete sub_boards.at(j);
        }

        return minEval;
    }
}