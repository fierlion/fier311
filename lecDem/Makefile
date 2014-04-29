# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 4

CC=gcc
#DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99
OBJ =stat
PROGS=stat


all: $(PROGS)

stat: stat.o
	$(CC) $(CFLAGS) -o stat stat.o

stat.o: stat.c
	$(CC) $(CFLAGS) -c stat.c

clean:
	rm -f $(PROGS) *.o *~

