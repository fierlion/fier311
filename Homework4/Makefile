# Ray Allan Foote
# footer@onid.oregonstate.edu
# CS311_400
# Assignment 4

CC=gcc
#DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99
OBJ =sig_demo myar
PROGS=sig_demo myar


all: $(PROGS)

sig_demo: sig_demo.o
	$(CC) $(CFLAGS) -o sig_demo sig_demo.o

sig_demo.o: sig_demo.c
	$(CC) $(CFLAGS) -c sig_demo.c

myar: myar.o $(DEPS)
	$(CC) $(CFLAGS) -o myar myar.o

myar.o: myar.c $(DEPS)
	$(CC) $(CFLAGS) -c myar.c

#tests as targets
testq12345:
	rm -f ar12345.ar
	rm -f myar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	./myar -q myar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	diff ar12345.ar myar12345.ar

testq135:
	rm -f ar135.ar
	rm -f myar135.ar
	ar q ar135.ar 1-s.txt 3-s.txt 5-s.txt
	./myar -q myar135.ar 1-s.txt 3-s.txt 5-s.txt
	diff ar135.ar myar135.ar

testq24:
	rm -f ar24.ar
	rm -f myar24.ar
	ar q ar24.ar 2-s.txt 4-s.txt
	./myar -q myar24.ar 2-s.txt 4-s.txt
	diff ar24.ar myar24.ar

testq: testq12345 testq135 testq24

clean:
	rm -f $(PROGS) *.o *~
	rm -f ar12345.ar ar24.ar ar135.ar
	rm -f myar12345.ar myar24.ar myar135.ar
