# Dots and Boxes (C)

A console-based Dots and Boxes game written in C for CMPS 241, designed to run on Alpine Linux inside a virtual machine.

## Sprint 1: Two-Player Game

- 4x5 grid of boxes (5 rows x 6 columns of dots)
- Players A and B take turns drawing a line between two adjacent dots
- Completing a box awards it to the player (their initial appears inside it) and gives them another turn
- The game ends when all 20 boxes are claimed; the player with the most boxes wins

## Build

    make

## Run

    ./dotsboxes

## How to play

On your turn, enter the row and column of the first dot, then the second dot:

    0 0 0 1

This draws a horizontal line between dot (0,0) and dot (0,1).

## Project structure

| File | Purpose |
|---|---|
| `src/board.h`, `src/board.c` | Grid data, drawing the board, validating and drawing lines, checking whether a box is complete |
| `src/game.h`, `src/game.c` | Turns, awarding boxes, scores, game loop and winner |
| `src/input.h`, `src/input.c` | Reading and validating player input |
| `src/main.c` | Entry point; starts a game and offers a rematch |
| `Makefile` | Builds `dotsboxes` |

## Debugging

    make valgrind   # valgrind --leak-check=full ./dotsboxes
    make gdb        # gdb ./dotsboxes

## License

MIT. See [LICENSE](LICENSE).
