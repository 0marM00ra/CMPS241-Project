#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>


#define DOT_ROWS 5
#define DOT_COLS 6
#define BOX_ROWS (DOT_ROWS - 1)
#define BOX_COLS (DOT_COLS - 1)
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)

#define NO_OWNER ' '


typedef struct {
    int r1, c1;
    int r2, c2;
} Move;

typedef enum {
    MOVE_OK,
    MOVE_OUT_OF_RANGE,
    MOVE_NOT_ADJACENT,
    MOVE_ALREADY_DRAWN
} MoveError;

typedef struct {
    bool h[DOT_ROWS][BOX_COLS];
    bool v[BOX_ROWS][DOT_COLS];
    char owner[BOX_ROWS][BOX_COLS];
} Board;

void board_init(Board *b);
void board_print(const Board *b);

/* Checks that a move is legal. On success, reorders the move so that
 * (r1, c1) is the top/left dot. */
MoveError board_check_move(const Board *b, Move *m);
const char *board_move_error_message(MoveError err);

void board_draw_line(Board *b, Move m);

bool board_box_complete(const Board *b, int r, int c);

#endif
