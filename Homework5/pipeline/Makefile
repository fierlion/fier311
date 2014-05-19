# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 5 pipeline Makefile

CC=gcc
CFLAGS=$(DEBUG) -Wall -std=c99 -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
OBJ = pipeline
PROGS= pipeline

all: $(PROGS)

pipes: pipeline.o
	$(CC) $(CFLAGS) -o pipeline pipeline.o

pipes.o: pipeline.c
	$(CC) $(CFLAGS) -c pipeline.c

#tests as targets
test:
	(rev | sort | uniq -c | tee comOut2 | wc) < words.txt > comOut1
	./pipeline -f progOut2 < words.txt > progOut1
	diff comOut2 progOut2
	diff comOut1 progOut1

clean:
	rm -f $(PROGS) *.o *~
	rm -f comOut1 comOut2
	rm -f progOut1 progOut2
