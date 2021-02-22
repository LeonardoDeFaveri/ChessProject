#ifndef PIECES_HPP
#define PIECES_HPP

/**
 * Pieces definitions constants.
 */
struct Pieces
{
    static const int PAWN = 1;
    static const int KNIGHT = 2;
    static const int BISHOP = 3;
    static const int ROCK = 4;
    static const int QUEEN = 5;
    static const int KING = 6;

    static const int WHITE = 8;
    static const int BLACK = 16;

    // Black pawn: Pieces::BLACK | Pieces::PAWN
};
//typedef struct Pieces Pieces;

/**
 * Gets the interger value of a piece by its SAN (Standard Algebraic Notation).
 * 
 * @param san_value SAN representation of the piece.
 * @return integer value.
 */
int get_value_from_SAN(char san_value);

/**
 * Gets the SAN (Standard Algebraic Notation) representation  by its integer value.
 * 
 * @param value integer value of the piece.
 * @return SAN representation.
 */
char get_SAN_from_value(int value);

#endif