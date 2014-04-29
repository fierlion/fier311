# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 3
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall
PROGS=homework3


all: $(PROGS)


homework3: homework3.o
	$(CC) $(CFLAGS) -o homework3 homework3.o

homework3.o: homework3.c
	$(CC) $(CFLAGS) -c homework3.c

clean:
	rm -f $(PROGS) *.o *~

