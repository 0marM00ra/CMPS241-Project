#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* start with every line undrawn and every box unowned */
void board_init(Board *b)
{
    memset(b, 0, sizeof *b);    /* sets all the lines to false */
    for (int r = 0; r < BOX_ROWS; r++) {
        for (int c = 0; c < BOX_COLS; c++) {
            b->owner[r][c] = NO_OWNER;
        }
    }
}

void board_print(const Board *b)
{
    /* column numbers on top */
    printf("  ");
    for (int c = 0; c < DOT_COLS; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < DOT_ROWS; r++) {
        /* row of dots with the horizontal lines between them */
        printf("%d ", r);
        for (int c = 0; c < DOT_COLS; c++) {
            putchar('.');
            if (c < BOX_COLS) {     /* the last dot has no line after it */
                putchar(b->h[r][c] ? '-' : ' ');
            }
        }
        printf("\n");

        /* row with the vertical lines and the box owners
           (the last row of dots has no boxes under it) */
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

/* checks that a dot is really on the board */
static bool dot_in_range(int r, int c)
{
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

MoveError board_check_move(const Board *b, Move *m)
{
    /* both dots must be on the board */
    if (!dot_in_range(m->r1, m->c1) || !dot_in_range(m->r2, m->c2)) {
        return MOVE_OUT_OF_RANGE;
    }

    /* the dots must be neighbours (distance of exactly 1, so no diagonals) */
    if (abs(m->r1 - m->r2) + abs(m->c1 - m->c2) != 1) {
        return MOVE_NOT_ADJACENT;
    }

    /* put the dots in order (top to bottom or left to right)
       so the same line is always stored the same way */
    if (m->r2 < m->r1 || m->c2 < m->c1) {
        Move swapped = { m->r2, m->c2, m->r1, m->c1 };
        *m = swapped;
    }

    /* same row means horizontal line, otherwise it's vertical */
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

/* assumes the move was already checked and the dots are in order */
void board_draw_line(Board *b, Move m)
{
    if (m.r1 == m.r2) {
        b->h[m.r1][m.c1] = true;
    } else {
        b->v[m.r1][m.c1] = true;
    }
}

/* a box is complete when top, bottom, left and right are all drawn */
bool board_box_complete(const Board *b, int r, int c)
{
    return b->h[r][c] && b->h[r + 1][c] && b->v[r][c] && b->v[r][c + 1];
}
