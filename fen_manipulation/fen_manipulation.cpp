#include "fen_manipulation.hpp"
#include <cctype>
#include <cstring>
#include <cstdlib>

/**
 * Converts a character representing a digit into its int value.
 * 
 * @param character character to convert. Before calling this function
 *      it is important to check whether this character is a valid digit
 *      or not.
 */
static int to_digit(char character) {
    int ris = 0;

    if (isdigit(character)) {
        character - '0';
    }
    
    return ris;
}

/**
 * Extracts the number of halfmove or fullmove clock from the fen string.
 * 
 * @param fen_string fen string from which extract the number.
 * @param move_clock variable in which store the value of halfmove or fullmove clock.
 * @return position of last character checked;
 */
static int get_move_clock(const char * fen_string, unsigned int &move_clock) {
    char * substring = new char[strlen(fen_string)];
    
    int i;
    for (i = 0; fen_string[i] != ' ' && fen_string[i] != '\0'; i++) {
        substring[i] = fen_string[i];
    }
    substring[i] = '\0';

    move_clock = atoi(substring);

    delete[] substring;
    return i;
}

bool check_fen_validity(const char * fen_string) {
    return false;
}

struct Board evaluate_fen(const char * fen_string) {
    Board board;

    int row = 0, column = 0;
    int index = 0;
    for (int index = 0; fen_string[index] != ' ' && fen_string[index] != '\0'; index++) {
        char character = fen_string[index];

        if (isdigit(character)) {
            column += to_digit(character); 
        } else if (character == '/') {
            row++;
            column = 0;
        } else {
            board.board[row][column] = get_value_from_SAN(character);
            column++;
        }
    }

    if (fen_string[index] == '\0') {
        board.white_plays = true;
        board.black_kingside = board.black_queenside = true;
        board.white_kingside = board.white_queenside = true;

        board.halfmove_clock = 0;
        board.fullmove_clock = 1;
    } else {
        index++;
        board.white_plays = fen_string[index] == 'w';

        // Castling authorization
        board.black_kingside = board.black_queenside = false;
        board.white_kingside = board.white_queenside = false;
        for (++index; fen_string[index] != ' ' && fen_string[index] != '\0'; index++) {
            switch (fen_string[index])
            {
            case 'k':
                board.black_kingside = true;
                break;

            case 'q':
                board.black_queenside = true;
                break;

            case 'K':
                board.white_kingside = true;
                break;
            
            case 'Q':
                board.white_queenside = true;
                break;
            }
        }

        index++;
        board.enpassant = fen_string[index] != '-';

        index = get_move_clock(fen_string + index + 1, board.halfmove_clock);
        index = get_move_clock(fen_string + index + 1, board.fullmove_clock);
    }

    return board;
}

char * generate_fen(const struct Board &board) {
    return NULL;
}