#ifndef FEN_MANIPULATION_HPP
#define FEN_MANIPULATION_HPP

#include "../board_and_pieces/board.hpp"
#include "../board_and_pieces/pieces.hpp"

/*
A FEN record contains six fields. The separator between fields is a space.
The fields are:
1.  Piece placement (from White's perspective). Each rank is described, starting with rank 8 and ending with rank 1;
    within each rank, the contents of each square are described from file "a" through file "h".
    Following the Standard Algebraic Notation (SAN), each piece is identified by a single letter taken from the standard 
    English names (pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K").
    
    White pieces are designated using upper-case letters ("PNBRQK") while black pieces use lowercase ("pnbrqk").
    Empty squares are noted using digits 1 through 8 (the number of empty squares), and "/" separates ranks.

2.  Active color. "w" means White moves next, "b" means Black moves next.

3.  Castling availability. If neither side can castle, this is "-". Otherwise, this has one or more letters:
    "K" (White can castle kingside), "Q" (White can castle queenside), "k" (Black can castle kingside),
    and/or "q" (Black can castle queenside).
    A move that temporarily prevents castling does not negate this notation.

4.  En passant target square in algebraic notation. If there's no en passant target square, this is "-".
    If a pawn has just made a two-square move, this is the position "behind" the pawn. This is recorded regardless 
    of whether there is a pawn in position to make an en passant capture.

5.  Halfmove clock: This is the number of halfmoves since the last capture or pawn advance.
    The reason for this field is that the value is used in the fifty-move rule.

6.  Fullmove number: The number of the full move. It starts at 1, and is incremented after Black's move.
*/

/**
 * FEN string that represent the initial game configuration.
 */
char const STD_FEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\0"; 

/**
 * Checks the correct composition of a fen string.
 * 
 * @param fen_string fen string to check.
 * @return true if the string is correct, otherwise false.
 */
bool check_fen_validity(const char * fen_string);

/**
 * Evaluates a fen string and return the associated game board.
 * 
 * @param fen_string position of the pieces according to the fen notation.
 * @return game board.
 */
struct Board evaluate_fen(const char * fen_string);

/**
 * Generates a fen string from a game board.
 * 
 * @param board game board for which generate fen representation.
 * @return fen string.
 */
char * generate_fen(const struct Board &board);

#endif