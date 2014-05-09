# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 5 pipeline Makefile

CC=gcc
#DEBUG=
CFLAGS=$(DEBUG) -Wall -std=c99 -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
OBJ = pipes
PROGS= pipes

all: $(PROGS)

pipes: pipes.o
	$(CC) $(CFLAGS) -o pipes pipes.o

pipes.o: pipes.c
	$(CC) $(CFLAGS) -c pipes.c

#tests as targets
test:
	(rev | sort)< simple1.txt > outfile1
	./pipes -f outfile2 < simple1.txt > outfile3
	diff outfile1 outfile2
#	(rev | sort | uniq -c | tee outfile2 | wc) < simple1.txt > outfile1

clean:
	rm -f $(PROGS) *.o *~
