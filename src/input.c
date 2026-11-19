#include "input.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 128

/* reads one line from the keyboard into buf
   returns false if there is nothing left to read */
static bool read_line(char *buf, size_t size)
{
    if (fgets(buf, (int)size, stdin) == NULL) {
        return false;
    }
    /* no newline means the line was longer than the buffer,
       so throw away the rest so it doesn't mess up the next read */
    if (strchr(buf, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
    return true;
}

bool input_read_move(const Board *b, char player, Move *out)
{
    char line[LINE_SIZE];

    /* loop until we get a valid move */
    while (true) {
        printf("Player %c's turn. Enter the row and column of the first dot "
               "(e.g., A0 -> 0 0) and second dot: ", player);
        fflush(stdout);

        if (!read_line(line, sizeof line)) {
            printf("\n");
            return false;
        }

        /* read 4 numbers, the 5th %c catches anything extra at the end */
        Move m;
        char extra;
        int count = sscanf(line, "%d %d %d %d %c", &m.r1, &m.c1, &m.r2, &m.c2, &extra);
        if (count != 4) {
            printf("Please enter exactly four numbers, e.g. 0 0 0 1\n");
            continue;
        }

        /* check the move against the board (range, adjacent, already drawn) */
        MoveError err = board_check_move(b, &m);
        if (err != MOVE_OK) {
            printf("%s\n", board_move_error_message(err));
            continue;
        }

        *out = m;
        return true;
    }
}

bool input_ask_play_again(void)
{
    char line[LINE_SIZE];

    while (true) {
        printf("Play again? (y/n): ");
        fflush(stdout);

        if (!read_line(line, sizeof line)) {
            printf("\n");
            return false;
        }

        /* only look at the first letter, and ignore upper or lower case */
        char answer = (char)tolower((unsigned char)line[0]);
        if (answer == 'y') {
            return true;
        }
        if (answer == 'n') {
            return false;
        }
        printf("Please type y or n.\n");
    }
}
