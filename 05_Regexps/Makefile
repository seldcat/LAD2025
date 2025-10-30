CC = gcc
CFLAGS = -Wall -Wextra -O2

all: esub

esub: esub.c
	$(CC) $(CFLAGS) -o esub esub.c

clean:
	rm -f esub *.o

test: esub
	./tests/run_tests.sh