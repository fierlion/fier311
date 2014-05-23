# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 6 Makefile

CC=gcc
CFLAGS= $(DEBUG) -Wall -std=c99
LFLAG= -lrt
PFLAG= -pthread
OBJ= primeMProc primePThread
PROGS= primeMProc primePThread

all: $(PROGS)

primeMProc: primeMProc.o
	$(CC) $(CFLAGS) $(LFLAG) -o primeMProc primeMProc.o

primeMProc.o: primeMProc.c
	$(CC) $(CFLAGS) $(LFLAG) -c primeMProc.c

primePThread: primePThread.0
	$(CC) $(CFLAGS) $(PFLAG) -o primePThread primePThread.o 

primePThread.0: primePThread.c
	$(CC) $(CFLAGS) $(PFLAG) -c primePThread.c

clean:
	rm -f $(PROGS) *.o *~
	rm -f primeMTest.txt
	bash clean.bash
