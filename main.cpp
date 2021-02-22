#include <iostream>
#include "board_and_pieces/board.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Board *board;

    initialize(board);
    if (board == NULL)
    {
        cout << "FEN string isn't valid" << endl;
    }
    else
    {
        char *string = get_ascii(board);
        cout << string;
        delete[] string;
    }

    return 0;
}