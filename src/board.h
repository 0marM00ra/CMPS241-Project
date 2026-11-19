#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>


/* board size: 5 rows x 6 columns of dots, which gives 4 x 5 boxes */
#define DOT_ROWS 5
#define DOT_COLS 6
#define BOX_ROWS (DOT_ROWS - 1)
#define BOX_COLS (DOT_COLS - 1)
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)

/* char shown inside a box that nobody owns yet */
#define NO_OWNER ' '


/* a move = a line between two dots (row, column of each dot) */
typedef struct {
    int r1, c1;
    int r2, c2;
} Move;

/* the possible results when we check a move */
typedef enum {
    MOVE_OK,
    MOVE_OUT_OF_RANGE,
    MOVE_NOT_ADJACENT,
    MOVE_ALREADY_DRAWN
} MoveError;

typedef struct {
    bool h[DOT_ROWS][BOX_COLS];     /* horizontal lines: h[r][c] is the line right of dot (r,c) */
    bool v[BOX_ROWS][DOT_COLS];     /* vertical lines: v[r][c] is the line under dot (r,c) */
    char owner[BOX_ROWS][BOX_COLS]; /* who owns each box ('A', 'B' or NO_OWNER) */
} Board;

/* sets up an empty board with no lines and no owners */
void board_init(Board *b);
/* prints the board to the console */
void board_print(const Board *b);

/* checks a move and fixes the dot order if needed (it can change m) */
MoveError board_check_move(const Board *b, Move *m);
/* turns an error code into a message for the player */
const char *board_move_error_message(MoveError err);

/* marks the line of the move as drawn */
void board_draw_line(Board *b, Move m);

/* true if all four sides of box (r, c) are drawn */
bool board_box_complete(const Board *b, int r, int c);

#endif
