CC = gcc
CFLAGS = -Wall -Wextra -O2

all: number-game

number-game: number-game.c
	$(CC) $(CFLAGS) -o $@ $<

doc:
	doxygen Doxyfile

clean:
	rm -f number-game
	rm -rf html latex
