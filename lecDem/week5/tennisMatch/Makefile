#
#	Oregon State University
#	R Jesse Chaney
#  chaneyr@eecs.orst.edu
#	CS311
#	2013-06-25
#

CC=gcc
DEBUG=-g

# enable lots of warning messages.
# i happen to like bcpl style comments, so i cannot use -pedantic
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROGS= tennisMatch_SysV \
	tennisMatch_POSIX \
	tennisMatch_PThreads \
	tennisMatch_Pipes \
	tennisMatch_Signals


all: $(PROGS)


# this version of the application uses SysV message queues
tennisMatch_SysV: tennisMatch_SysV.o tennisMatch_Common.o
	$(CC) $(CFLAGS) -o tennisMatch_SysV tennisMatch_SysV.o tennisMatch_Common.o

tennisMatch_SysV.o: tennisMatch_SysV.c tennisMatch_SysV.h tennisMatch_Common.h
	$(CC) $(CFLAGS) -c tennisMatch_SysV.c


# this version of the application uses POSIX message queues
tennisMatch_POSIX: tennisMatch_POSIX.o tennisMatch_Common.o
	$(CC) $(CFLAGS) -o tennisMatch_POSIX tennisMatch_POSIX.o tennisMatch_Common.o -lrt

tennisMatch_POSIX.o: tennisMatch_POSIX.c tennisMatch_POSIX.h tennisMatch_Common.h
	$(CC) $(CFLAGS) -c tennisMatch_POSIX.c


# this version of the application uses POSIX message queues
tennisMatch_PThreads: tennisMatch_PThreads.o tennisMatch_Common.o
	$(CC) $(CFLAGS) -o tennisMatch_PThreads tennisMatch_PThreads.o tennisMatch_Common.o -lrt

tennisMatch_PThreads.o: tennisMatch_PThreads.c tennisMatch_PThreads.h tennisMatch_Common.h
	$(CC) $(CFLAGS) -c tennisMatch_PThreads.c


# this version of the application uses Pipes
tennisMatch_Pipes: tennisMatch_Pipes.o tennisMatch_Common.o
	$(CC) $(CFLAGS) -o tennisMatch_Pipes tennisMatch_Pipes.o tennisMatch_Common.o

tennisMatch_Pipes.o: tennisMatch_Pipes.c tennisMatch_Pipes.h tennisMatch_Common.h
	$(CC) $(CFLAGS) -c tennisMatch_Pipes.c


# this version of the application uses Pipes
tennisMatch_Signals: tennisMatch_Signals.o tennisMatch_Common.o
	$(CC) $(CFLAGS) -o tennisMatch_Signals tennisMatch_Signals.o tennisMatch_Common.o

tennisMatch_Signals.o: tennisMatch_Signals.c tennisMatch_Signals.h tennisMatch_Common.h
	$(CC) $(CFLAGS) -c tennisMatch_Signals.c
	

# this module is common to all programs.
tennisMatch_Common.o: tennisMatch_Common.c tennisMatch_Common.h
	$(CC) $(CFLAGS) -c tennisMatch_Common.c


# Just an example of how you can have an entry in the Makefile to run make
# and (maybe) change some default values.
opt: 
	$(MAKE) clean
	$(MAKE) DEBUG=-O3
	strip $(PROGS)

# clean up the compiled files
clean:
	rm -f $(PROGS) *.o *~ \#*

tar:	
	tar cvfj tennisMatch.tar.bzip *.[ch] Makefile
