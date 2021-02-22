#ifndef BOARD_HPP
#define BOARD_HPP

#include "../fen_manipulation/fen_manipulation.hpp"
#include "pieces.hpp"

const int ROWS = 8;
const int COLUMNS = 8;

/**
 * The matrix that represents the game board.
 */
struct Board
{
    int board[ROWS][COLUMNS] = {{0}};
    bool white_plays;

    // Castling options
    bool white_kingside;
    bool white_queenside;
    bool black_kingside;
    bool black_queenside;

    bool enpassant;

    unsigned int halfmove_clock;
    unsigned int fullmove_clock;
};

extern char const STD_FEN[];

/**
 * Initialize the board by positioning pieces.
 * 
 * @param board board structure's reference.
 * @param fen_string [OPTIONAL] position of the pieces according to the fen notation.
 *      If not provided standard positiong is intended.
 */
void initialize(Board &board, const char *fen_string = STD_FEN);

/**
 * Gets the ascii representation of the game board.
 * 
 * @param board game board.
 * @return ascii string. 
 */
char *get_ascii(const Board &board);

#endif