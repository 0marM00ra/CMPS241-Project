CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -g
TARGET  = dotsboxes

SRCS    = $(wildcard src/*.c)
OBJS    = $(SRCS:.c=.o)
HEADERS = $(wildcard src/*.h)

.PHONY: all run valgrind gdb clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rebuild every object if any header changes
src/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
