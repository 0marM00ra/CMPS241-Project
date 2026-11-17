#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void board_init(Board *b)
{
    memset(b, 0, sizeof *b);
    for (int r = 0; r < BOX_ROWS; r++) {
        for (int c = 0; c < BOX_COLS; c++) {
            b->owner[r][c] = NO_OWNER;
        }
    }
}

void board_print(const Board *b)
{
    printf("  ");
    for (int c = 0; c < DOT_COLS; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < DOT_ROWS; r++) {
        printf("%d ", r);
        for (int c = 0; c < DOT_COLS; c++) {
            putchar('.');
            if (c < BOX_COLS) {
                putchar(b->h[r][c] ? '-' : ' ');
            }
        }
        printf("\n");

        if (r < BOX_ROWS) {
            printf("  ");
            for (int c = 0; c < DOT_COLS; c++) {
                putchar(b->v[r][c] ? '|' : ' ');
                if (c < BOX_COLS) {
                    putchar(b->owner[r][c]);
                }
            }
            printf("\n");
        }
    }
}

static bool dot_in_range(int r, int c)
{
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

MoveError board_check_move(const Board *b, Move *m)
{
    if (!dot_in_range(m->r1, m->c1) || !dot_in_range(m->r2, m->c2)) {
        return MOVE_OUT_OF_RANGE;
    }

    if (abs(m->r1 - m->r2) + abs(m->c1 - m->c2) != 1) {
        return MOVE_NOT_ADJACENT;
    }

    if (m->r2 < m->r1 || m->c2 < m->c1) {
        Move swapped = { m->r2, m->c2, m->r1, m->c1 };
        *m = swapped;
    }

    bool horizontal = (m->r1 == m->r2);
    bool drawn = horizontal ? b->h[m->r1][m->c1] : b->v[m->r1][m->c1];
    if (drawn) {
        return MOVE_ALREADY_DRAWN;
    }

    return MOVE_OK;
}

const char *board_move_error_message(MoveError err)
{
    switch (err) {
    case MOVE_OUT_OF_RANGE:
        return "Those dots are off the board. Rows go from 0 to 4, columns from 0 to 5.";
    case MOVE_NOT_ADJACENT:
        return "The two dots must be next to each other (no diagonals).";
    case MOVE_ALREADY_DRAWN:
        return "That line is already drawn.";
    case MOVE_OK:
    default:
        return "";
    }
}

void board_draw_line(Board *b, Move m)
{
    if (m.r1 == m.r2) {
        b->h[m.r1][m.c1] = true;
    } else {
        b->v[m.r1][m.c1] = true;
    }
}

bool board_box_complete(const Board *b, int r, int c)
{
    return b->h[r][c] && b->h[r + 1][c] && b->v[r][c] && b->v[r][c + 1];
}
