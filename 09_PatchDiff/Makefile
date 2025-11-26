CC = gcc
CFLAGS = -Wall -Wextra -O2

all: maze_v1 maze_v2 maze_v3 maze_v4

maze_v2.c: maze_v1.c maze_v1_to_v2.patch
	patch -o $@ $< maze_v1_to_v2.patch

maze_v3.c: maze_v2.c maze_v2_to_v3.patch
	patch -o $@ $< maze_v2_to_v3.patch

maze_v4.c: maze_v3.c maze_v3_to_v4.patch
	patch -o $@ $< maze_v3_to_v4.patch

maze_v1: maze_v1.c
	$(CC) $(CFLAGS) -o $@ $<

maze_v2: maze_v2.c
	$(CC) $(CFLAGS) -o $@ $<

maze_v3: maze_v3.c
	$(CC) $(CFLAGS) -o $@ $<

maze_v4: maze_v4.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	./maze_v1
	./maze_v2 6
	./maze_v3 ".#" 6
	./maze_v4 42 ".#" 6

clean:
	rm -f maze_v2.c maze_v3.c maze_v4.c
	rm -f maze_v1 maze_v2 maze_v3 maze_v4
