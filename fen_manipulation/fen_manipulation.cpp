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
static int to_digit(char character);

/**
 * Splits a FEN string into its components.
 * 
 * @param fen_string fen string to split.
 * @return components of the FEN string.
 */
static FEN_string *split_fen_string(const char *fen_string);

//-----------------------------------------------------------------------------

bool check_fen_validity(const char *fen_string)
{
    return false;
}

struct Board evaluate_fen(const char *fen_string)
{
    Board board;

    FEN_string *components = split_fen_string(fen_string);

    int row = 0, column = 0;
    for (int i = 0; components->pieces[i] != '\0'; i++)
    {
        char character = components->pieces[i];

        if (isdigit(character))
        {
            column += to_digit(character);
        }
        else if (character == '/')
        {
            row++;
            column = 0;
        }
        else
        {
            board.board[row][column] = get_value_from_SAN(character);
            column++;
        }
    }

    board.white_plays = (components->next_player == 'w');

    // Castling authorization
    board.black_kingside = board.black_queenside = false;
    board.white_kingside = board.white_queenside = false;

    for (int i = 0; components->castling_options[i] != '\0'; i++)
    {
        switch (components->castling_options[i])
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

    board.enpassant = (components->enpassant[0] != '-');
    board.halfmove_clock = atoi(components->halfmove_clock);
    board.fullmove_clock = atoi(components->fullmve_clock);

    return board;
}

char *generate_fen(const struct Board &board)
{
    return NULL;
}

//-----------------------------------------------------------------------------
static int to_digit(char character)
{
    int ris = 0;

    if (isdigit(character))
    {
        character - '0';
    }

    return ris;
}

static FEN_string *split_fen_string(const char *fen_string)
{
    FEN_string *components = new FEN_string;
    int start, end;
    start = end = 0;

    while (fen_string[end] != ' ')
    {
        end++;
    }

    components->pieces = new char[end + 1];
    components->pieces[end] = '\0';
    for (int i = 0; i < end; i++)
    {
        components->pieces[i] = fen_string[i];
    }

    components->next_player = fen_string[end + 1];

    end += 3;
    start = end;
    while (fen_string[end] != ' ')
    {
        end++;
    }

    components->castling_options = new char[end - start + 1];
    components->castling_options[end] = '\0';
    for (int i = start; i < end; i++)
    {
        components->castling_options[i - start] = fen_string[i];
    }

    end += 1;
    start = end;
    while (fen_string[end] != ' ')
    {
        end++;
    }
    
    components->enpassant = new char[end - start + 1];
    components->enpassant[end] = '\0';
    for (int i = start; i < end; i++)
    {
        components->enpassant[i - start] = fen_string[i];
    }

    end += 1;
    start = end;
    while (fen_string[end] != ' ')
    {
        end++;
    }
    
    components->halfmove_clock = new char[end - start + 1];
    components->halfmove_clock[end] = '\0';
    for (int i = start; i < end; i++)
    {
        components->halfmove_clock[i - start] = fen_string[i];
    }
    
    end += 1;
    start = end;
    while (fen_string[end] != '\0')
    {
        end++;
    }
    
    components->fullmve_clock = new char[end - start + 1];
    components->fullmve_clock[end] = '\0';
    for (int i = start; i < end; i++)
    {
        components->fullmve_clock[i - start] = fen_string[i];
    }

    return components;
}