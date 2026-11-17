#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "board.h"

typedef struct {
    Board board;
    char current;
    int score_a;
    int score_b;
} Game;

void game_init(Game *g);

int game_apply_move(Game *g, Move m);

bool game_is_over(const Game *g);
void game_print_scores(const Game *g);
void game_print_result(const Game *g);

bool game_play(Game *g);

#endif
