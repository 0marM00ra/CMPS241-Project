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

## Debugging

    valgrind --leak-check=full ./dotsboxes
    gdb ./dotsboxes

## License

MIT. See [LICENSE](LICENSE).
