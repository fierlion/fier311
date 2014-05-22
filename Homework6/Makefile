# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 6 Makefile

CC=gcc
CFLAGS=$(DEBUG) -Wall -std=c99 -lrt
OBJ = primeMProc
PROGS= primeMProc

all: $(PROGS)

primeMProc: primeMProc.o
	$(CC) $(CFLAGS) -o primeMProc primeMProc.o

primeMProc.o: primeMProc.c
	$(CC) $(CFLAGS) -c primeMProc.c

#tests as targets
test:

clean:
	rm -f $(PROGS) *.o *~
	bash clean.bash
