SOURCES = src/main.c src/board.c src/input.c src/game.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -g -c
OUTPUT = dotsboxes

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

src/main.o: src/main.c src/game.h src/input.h src/board.h
	$(CC) $(CFLAGS) -o $@ $<

src/board.o: src/board.c src/board.h
	$(CC) $(CFLAGS) -o $@ $<

src/input.o: src/input.c src/input.h src/board.h
	$(CC) $(CFLAGS) -o $@ $<

src/game.o: src/game.c src/game.h src/input.h src/board.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	@rm -rf src/*.o $(OUTPUT)
