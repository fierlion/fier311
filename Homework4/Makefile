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

testt12345:
	rm -f ar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	ar t ar12345.ar > ar12345-ctoc.txt
	./myar -t ar12345.ar > myar12345-ctoc.txt
	diff ar12345-ctoc.txt myar12345-ctoc.txt

testt135:
	rm -f ar135.ar
	ar q ar135.ar 1-s.txt 3-s.txt 5-s.txt
	ar t ar135.ar > ar135-ctoc.txt
	./myar -t ar135.ar > myar135-ctoc.txt
	diff ar135-ctoc.txt myar135-ctoc.txt

test24:
	rm -f ar24.ar
	ar q ar24.ar 2-s.txt 4-s.txt
	ar t ar24.ar > ar24-ctoc.txt
	./myar -t ar24.ar > myar24-ctoc.txt
	diff ar24-ctoc.txt myar24-ctoc.txt

testt: testt12345 testt135 testt24

testv12345:
	rm -f ar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	ar tv ar12345.ar > ar12345-vtoc.txt
	./myar -v ar12345.ar > myar12345-vtoc.txt
	diff ar12345-vtoc.txt myar12345-vtoc.txt

testv135:
	rm -f ar135.ar
	ar q ar135.ar 1-s.txt 3-s.txt 5-s.txt
	ar tv ar135.ar > ar135-vtoc.txt
	./myar -v ar135.ar > myar135-vtoc.txt
	diff ar135-vtoc.txt myar135-vtoc.txt

test24:
	rm -f ar24.ar
	ar q ar24.ar 2-s.txt 4-s.txt
	ar tv ar24.ar > ar24-vtoc.txt
	./myar -t ar24.ar > myar24-vtoc.txt
	diff ar24-vtoc.txt myar24-vtoc.txt

testt: testv12345 testv135 testv24

tests: testq testt testv

	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
clean:
	rm -f $(PROGS) *.o *~
	rm -f ar12345.ar ar24.ar ar135.ar
	rm -f myar12345.ar myar24.ar myar135.ar
