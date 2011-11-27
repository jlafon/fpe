CC = gcc

CFLAGS = -Wall -ansi -Wno-unknown-pragmas

MATHLIB = -lm

SRC = testfpe.c
all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(MATHLIB) -o testfpe

clean:
	rm -f testfpe

