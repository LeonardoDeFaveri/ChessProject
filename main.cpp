#include <iostream>
#include "board_and_pieces/board.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Board board;

    initialize(board);
    char *string = get_ascii(board);
    cout << string << endl;
    delete[] string;

    return 0;
}