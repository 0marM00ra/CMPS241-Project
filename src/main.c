#include <stdio.h>

#include "game.h"
#include "input.h"

int main(void)
{
    printf("=== Dots and Boxes ===\n");
    printf("Draw lines between neighbouring dots. Complete a box to claim it\n");
    printf("and play again. The player with the most boxes wins.\n\n");

    /* play one game, then ask if they want another */
    do {
        Game game;
        game_init(&game);

        /* false means the input ended early, so just quit */
        if (!game_play(&game)) {
            return 0;
        }
        game_print_result(&game);
    } while (input_ask_play_again());

    printf("Thanks for playing!\n");
    return 0;
}
