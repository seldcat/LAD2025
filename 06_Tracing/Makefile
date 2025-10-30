CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -g
LDFLAGS =

.PHONY: all test clean

all: move libprotect.so

move: move.o
	$(CC) $(CFLAGS) -o $@ $^

move.o: move.c
	$(CC) $(CFLAGS) -c $<

libprotect.so: protect.o
	$(CC) -shared -fPIC -o $@ $^ -ldl

protect.o: protect.c
	$(CC) $(CFLAGS) -fPIC -c $<

test: all
	cd tests && ./run_tests.sh

clean:
	rm -f move libprotect.so *.o
	cd tests && rm -f *.tmp *.log *.out infile* outfile* PROTECT_* 2>/dev/null || true
