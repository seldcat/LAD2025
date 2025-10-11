CC      = gcc
CFLAGS  = -O0 -g -Wall -Wextra -std=c11

.PHONY: all test clean

all: range

range: range.c
	$(CC) $(CFLAGS) -o range range.c

test: range
	@echo "Running GDB test 1 (1 12, multiples of 5)..."
	@gdb --batch --quiet -x test1.gdb | grep '^@@@' > out1.txt
	@diff -u expected1.txt out1.txt
	@echo "Test 1 OK"
	@echo "Running GDB test 2 (-100 100 3, indices 28-35)..."
	@gdb --batch --quiet -x test2.gdb | grep '^@@@' > out2.txt
	@diff -u expected2.txt out2.txt
	@echo "Test 2 OK"
	@echo "All tests passed."

clean:
	rm -f range out1.txt out2.txt
