#include <iostream>
#include <iomanip>
#include "../includes/AInterface.hpp"

void AInterface::showScores() const
{
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
        {
            std::cout << std::endl;
        }
        
        std::cout << std::setw(4) << scores[i] << "\t";
    }
}