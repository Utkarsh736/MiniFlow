CC = gcc
CFLAGS = -fPIC -Wall -Wextra
LDFLAGS = -shared

all: libminitensor.so

libminitensor.so: minitensor.o
	$(CC) $(LDFLAGS) -o $@ $^

minitensor.o: minitensor.c minitensor.h
	$(CC) $(CFLAGS) -c -o $@ $<

test: test.c libminitensor.so
	$(CC) test.c -L. -lminitensor -o test
	LD_LIBRARY_PATH=. ./test

clean:
	rm -f *.o *.so test