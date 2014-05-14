# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 5 uniqify Makefile

CC=gcc
CFLAGS=$(DEBUG) -Wall -std=c99 -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
OBJ = uniqify
PROGS= uniqify

all: $(PROGS)

uniqify: uniqify.o
	$(CC) $(CFLAGS) -o uniqify uniqify.o

uniqify.o: uniqify.c
	$(CC) $(CFLAGS) -c uniqify.c

#tests as targets
test:
	./uniqify -n 5 < websters.txt > uniqTestOut
	bash uniqify.bash < websters.txt > bashTestOut
	diff uniqTestOut bashTestOut
clean:
	rm -f $(PROGS) *.o *~
	rm -f uniqTestOut
	rm -f bashTestOut
