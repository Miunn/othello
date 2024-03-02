#include <iostream>
#include <bits/stdc++.h> 
#include "../includes/MinMax.hpp"

MinMax::MinMax(int depth)
{
    this->player = Pawn::BLACK;
    this->ennemy = Pawn::WHITE;
    this->depth = depth;
}

MinMax::MinMax(Pawn player, int depth)
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
}

int MinMax::heuristic(const Board &B) const
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

std::vector<Board*> MinMax::computeSubBoards(const Board &board, Pawn pawn) const
{
    std::vector<Board*> depth_boards = {};
    std::vector<std::string> moves = board.getValidMoves(pawn);
    for (int j = 0; j < (int)moves.size(); j++)
    {
        Board *copy_board = new Board(board);
        copy_board->play(pawn, moves.at(j));
        depth_boards.push_back(copy_board);
    }
    return depth_boards;
}

std::string MinMax::play(const Board &board) const
{
    std::vector<std::string> moves = board.getValidMoves(this->player);
    std::vector<int> scores = {};
    for (int i = 0; i < (int) moves.size(); i++)
    {
        scores.push_back(play_research(board, 0));
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

int MinMax::play_research(const Board &board, int depth) const
{
    std::cout << "Called play research at depth:" << depth << std::endl;
    if (this->depth == depth)
    {
        std::cout << "Max depth reached, send heuristic score -> " << this->heuristic(board) << std::endl;
        return this->heuristic(board);
    }


    std::vector<Board*> sub_boards;
    if (depth % 2 == 0)
    {
        sub_boards = this->computeSubBoards(board, this->player);
    }
    else
    {
        sub_boards = this->computeSubBoards(board, this->ennemy);
    }
    std::vector<int> scores = {};

    std::cout << "Computed board for d=" << depth << ": " << sub_boards.size() << std::endl;
    for (int i = 0; i < (int)sub_boards.size(); i++)
    {
        std::cout << "Subboard " << i << ":" << std::endl;
        std::cout << *sub_boards.at(i) << std::endl;
    }

    for (int i = 0; i < (int)sub_boards.size(); i++)
    {
        scores.push_back(this->play_research(*sub_boards.at(i), depth+1));
    }

    if (depth % 2 == 0)
    {
        std::cout << "Get max of: ";
        for (int i = 0; i < (int) scores.size(); i++)
        {
            std::cout << scores.at(i) << " ";
        }
        std::cout << std::endl;
        return (int) *std::max_element(scores.begin(), scores.end());
    }
    else
    {
        std::cout << "Get min of: ";
        for (int i = 0; i < (int) scores.size(); i++)
        {
            std::cout << scores.at(i) << " ";
        }
        std::cout << std::endl;
        return (int) *std::min_element(scores.begin(), scores.end());
    }
}