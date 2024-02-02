#include <iostream>
#include "../includes/Board.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    Board b;

    cout << b << endl;
    
    std::vector<string> validBlack = b.getValidMove(WHITE);

    for (int i = 0; i < (int) validBlack.size(); i ++)
    {
        cout << validBlack[i] << " ";
    }
    cout << endl;

    return 0;
}