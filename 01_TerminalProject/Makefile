CC      := cc
CFLAGS  := -std=c11 -Wall -Wextra -O2
LDFLAGS := -lncurses

.PHONY: all clean

all: Show

Show: Show.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

Show.o: Show.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) Show Show.o

