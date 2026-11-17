#include "input.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 128

static bool read_line(char *buf, size_t size)
{
    if (fgets(buf, (int)size, stdin) == NULL) {
        return false;
    }
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

    while (true) {
        printf("Player %c's turn. Enter the row and column of the first dot "
               "(e.g., A0 -> 0 0) and second dot: ", player);
        fflush(stdout);

        if (!read_line(line, sizeof line)) {
            printf("\n");
            return false;
        }

        Move m;
        char extra;
        int count = sscanf(line, "%d %d %d %d %c", &m.r1, &m.c1, &m.r2, &m.c2, &extra);
        if (count != 4) {
            printf("Please enter exactly four numbers, e.g. 0 0 0 1\n");
            continue;
        }

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
