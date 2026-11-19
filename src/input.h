#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "board.h"

/* keeps asking the player until they enter a valid move, then stores it in out
   returns false if the input ended (like Ctrl+D) */
bool input_read_move(const Board *b, char player, Move *out);

/* asks "Play again?" and returns true for y, false for n */
bool input_ask_play_again(void);

#endif
