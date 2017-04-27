# Makefile for 'crawler'
#
# Savannah Liu, April 2017
L = ../libcs50
PROG = crawler
OBJS = crawler.o 
LIBS = -lcurl
LLIBS = $L/libcs50.a # local library

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -g -I$L
CC = gcc
MAKE = make

.PHONY: all clean

all: $(PROG)

# executable depends on object files
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

# object files depend on include files
crawler.o: $L/bag.h $L/file.h $L/memory.h $L/hashtable.h $L/webpage.h


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
