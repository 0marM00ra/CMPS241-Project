#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "board.h"

bool input_read_move(const Board *b, char player, Move *out);

bool input_ask_play_again(void);

#endif
