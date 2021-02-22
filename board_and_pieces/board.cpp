#include "board.hpp"

void initialize(Board &board, const char *fen_string)
{
    board = evaluate_fen(fen_string);
}

char *get_ascii(const Board &board)
{
    char *string = new char[ROWS * COLUMNS + 1];

    int index = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int ii = 0; ii < COLUMNS; ii++)
        {
            string[index++] = get_SAN_from_value(board.board[i][ii]);
        }
        string[index++] = '\n';
    }

    string[index] = '\0';
    return string;
}