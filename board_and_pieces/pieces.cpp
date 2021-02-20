#include "pieces.hpp"

int get_value_from_SAN(char san_value) {
    int value;

    switch (san_value) {
    // Black pieces
    case 'r':
        value = Pieces::BLACK | Pieces::ROCK;
        break;

    case 'n':
        value = Pieces::BLACK | Pieces::KNIGHT;
        break;

    case 'b':
        value = Pieces::BLACK | Pieces::BISHOP;
        break;

    case 'q':
        value = Pieces::BLACK | Pieces::QUEEN;
        break;

    case 'k':
        value = Pieces::BLACK | Pieces::KING;
        break;

    case 'p':
        value = Pieces::BLACK | Pieces::PAWN;
        break;

    // White pieces
    case 'R':
        value = Pieces::WHITE | Pieces::ROCK;
        break;

    case 'N':
        value = Pieces::WHITE | Pieces::KNIGHT;
        break;

    case 'B':
        value = Pieces::WHITE | Pieces::BISHOP;
        break;

    case 'Q':
        value = Pieces::WHITE | Pieces::QUEEN;
        break;

    case 'K':
        value = Pieces::WHITE | Pieces::KING;
        break;

    case 'P':
        value = Pieces::WHITE | Pieces::PAWN;
        break;
    }

    return value;
}

char get_SAN_from_value(int value) {
    char character;

    switch (value) {
    // Black pieces
    case Pieces::BLACK | Pieces::PAWN:
        character = 'p';
        break;

    case Pieces::BLACK | Pieces::ROCK:
        character = 'r';
        break;

    case Pieces::BLACK | Pieces::KNIGHT:
        character = 'n';
        break;

    case Pieces::BLACK | Pieces::BISHOP:
        character = 'b';
        break;

    case Pieces::BLACK | Pieces::QUEEN:
        character = 'q';
        break;

    case Pieces::BLACK | Pieces::KING:
        character = 'k';
        break;

    // White pieces
    case Pieces::WHITE | Pieces::PAWN:
        character = 'P';
        break;

    case Pieces::WHITE | Pieces::ROCK:
        character = 'R';
        break;

    case Pieces::WHITE | Pieces::KNIGHT:
        character = 'N';
        break;

    case Pieces::WHITE | Pieces::BISHOP:
        character = 'B';
        break;

    case Pieces::WHITE | Pieces::QUEEN:
        character = 'Q';
        break;

    case Pieces::WHITE | Pieces::KING:
        character = 'K';
        break;

    case 0:
        character = ' ';
        break;
    }

    return character;
}