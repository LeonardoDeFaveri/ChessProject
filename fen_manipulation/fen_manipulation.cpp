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
    bool result = true;
    int index = 0;

    int rows = 1, columns = 0;
    int white_kings_counter = 0, black_kings_counter = 0;
    bool slash_expected = false;
    while (result && fen_string[index] != ' ')
    {
        char character = fen_string[index];

        if (character == '\0')
        {
            result = false;
        }
        else if (isdigit(character))
        {
            columns += to_digit(character);
            slash_expected = (columns % COLUMNS == 0);
        }
        else if (character == '/')
        {
            result = slash_expected;
            if (result)
            {
                slash_expected = false;
                columns = 0;
                rows++;
            }
        }
        else
        {
            result = (strchr(SAN_CHARACTER, character) != NULL);
            if (result)
            {
                columns++;
                slash_expected = (columns % COLUMNS == 0);
                if (character == 'k')
                {
                    black_kings_counter++;
                    result = (black_kings_counter == 1);
                }
                else if (character == 'K')
                {
                    white_kings_counter++;
                    result = (white_kings_counter == 1);
                }
            }
        }

        index++;
    }
    result = (rows == 8 && columns == 8);

    if (result)
    {
        index++;
        result = (fen_string[index] == 'b' || fen_string[index] == 'w');

        index += 2;
        while (result && fen_string[index] != ' ')
        {
            char character = fen_string[index];

            if (character == '\0')
            {
                result = false;
            }
            else
            {
                result = (strchr(CASLTING_OPTIONS_CHARACTERS, character) != NULL);
            }

            index++;
        }

        index++;
        if (fen_string[index] == '-' && fen_string[index + 1] == ' ')
        {
            result = true;
            index += 2;
        }
        else if (strchr(FILE_LETTERS, fen_string[index]) != NULL &&
                 (fen_string[index + 1] == '3' || fen_string[index + 1] == '6') &&
                 fen_string[index + 2] == ' ')
        {
            result = true;
            index += 3;
        }
        else
        {
            result = false;
        }

        while (result && fen_string[index] != ' ')
        {
            if (fen_string[index] == '\0')
            {
                result = false;
            }
            else
            {
                result = isdigit(fen_string[index]);
            }

            index++;
        }
        
        index++;
        while (result && fen_string[index] != '\0')
        {
            if (fen_string[index] == ' ')
            {
                result = false;
            }
            else
            {
                result = isdigit(fen_string[index]);
            }

            index++;
        }
    }

    return result;
}

struct Board *evaluate_fen(const char *fen_string)
{
    if(!check_fen_validity(fen_string))
    {
        return NULL;
    }

    Board *board = new Board;
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
            board->board[row][column] = get_value_from_SAN(character);
            column++;
        }
    }

    board->white_plays = (components->next_player == 'w');

    // Castling authorization
    board->black_kingside = board->black_queenside = false;
    board->white_kingside = board->white_queenside = false;

    for (int i = 0; components->castling_options[i] != '\0'; i++)
    {
        switch (components->castling_options[i])
        {
        case 'k':
            board->black_kingside = true;
            break;

        case 'q':
            board->black_queenside = true;
            break;

        case 'K':
            board->white_kingside = true;
            break;

        case 'Q':
            board->white_queenside = true;
            break;
        }
    }

    board->enpassant = (components->enpassant[0] != '-');
    board->halfmove_clock = atoi(components->halfmove_clock);
    board->fullmove_clock = atoi(components->fullmve_clock);

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
        ris = character - '0';
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