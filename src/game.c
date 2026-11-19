#include "game.h"

#include <stdio.h>

#include "input.h"

#define SEPARATOR "***********************************************************************"

void game_init(Game *g)
{
    board_init(&g->board);
    g->current = 'A';
    g->score_a = 0;
    g->score_b = 0;
}

/* gives box (r, c) to the current player if it is now complete
   returns 1 if the box was claimed, 0 if not */
static int try_claim(Game *g, int r, int c)
{
    /* boxes next to the edge of the board don't exist, so skip them */
    if (r < 0 || r >= BOX_ROWS || c < 0 || c >= BOX_COLS) {
        return 0;
    }
    /* skip boxes that are already taken or still missing a side */
    if (g->board.owner[r][c] != NO_OWNER || !board_box_complete(&g->board, r, c)) {
        return 0;
    }

    g->board.owner[r][c] = g->current;
    if (g->current == 'A') {
        g->score_a++;
    } else {
        g->score_b++;
    }
    return 1;
}

int game_apply_move(Game *g, Move m)
{
    board_draw_line(&g->board, m);

    /* a line touches at most 2 boxes, so only check those */
    int completed = 0;
    if (m.r1 == m.r2) {
        completed += try_claim(g, m.r1 - 1, m.c1); /* box above */
        completed += try_claim(g, m.r1, m.c1);     /* box below */
    } else {
        completed += try_claim(g, m.r1, m.c1 - 1); /* box to the left */
        completed += try_claim(g, m.r1, m.c1);     /* box to the right */
    }

    /* Completing a box earns another turn */
    if (completed == 0) {
        g->current = (g->current == 'A') ? 'B' : 'A';
    }
    return completed;
}

/* the game ends when every box has an owner */
bool game_is_over(const Game *g)
{
    return g->score_a + g->score_b == TOTAL_BOXES;
}

void game_print_scores(const Game *g)
{
    printf("%s\n", SEPARATOR);
    printf("Player A score: %d\n", g->score_a);
    printf("Player B score: %d\n", g->score_b);
    printf("%s\n", SEPARATOR);
}

/* shows the final board, the scores and who won */
void game_print_result(const Game *g)
{
    printf("\nGame over!\n");
    board_print(&g->board);
    game_print_scores(g);

    if (g->score_a > g->score_b) {
        printf("Player A wins %d to %d!\n", g->score_a, g->score_b);
    } else if (g->score_b > g->score_a) {
        printf("Player B wins %d to %d!\n", g->score_b, g->score_a);
    } else {
        printf("It's a tie, %d to %d!\n", g->score_a, g->score_b);
    }
}

bool game_play(Game *g)
{
    while (!game_is_over(g)) {
        board_print(&g->board);

        /* ask the current player for a move (already checked by input.c) */
        Move m;
        if (!input_read_move(&g->board, g->current, &m)) {
            return false;   /* input ended, so stop the game */
        }

        int completed = game_apply_move(g, m);
        game_print_scores(g);
        /* if they completed a box the turn did not switch, so current is still them */
        if (completed > 0 && !game_is_over(g)) {
            printf("Player %c completed %d box%s and plays again!\n",
                   g->current, completed, completed == 1 ? "" : "es");
        }
    }
    return true;
}
