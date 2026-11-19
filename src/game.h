#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "board.h"

/* everything about one game: the board, whose turn it is and the scores */
typedef struct {
    Board board;
    char current;   /* 'A' or 'B' */
    int score_a;
    int score_b;
} Game;

/* starts a new game, player A goes first */
void game_init(Game *g);

/* draws the line and claims any boxes it completes,
   returns how many boxes were completed */
int game_apply_move(Game *g, Move m);

bool game_is_over(const Game *g);
void game_print_scores(const Game *g);
void game_print_result(const Game *g);

/* runs the whole game loop, returns false if the input ended early */
bool game_play(Game *g);

#endif
