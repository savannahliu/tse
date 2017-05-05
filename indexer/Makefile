# Makefile for 'indexer'
#
# Savannah Liu, April 2017
C = ../common
L = ../libcs50
PROG = indexer
OBJS = indexer.o
LIBS = -lcurl
LLIBS = $C/common.a $L/libcs50.a # local libraries

# uncomment -DMEMTEST to turn on verbose memory logging
# run 'make clean; make' whenever you change this
FLAGS = #-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
CC = gcc
MAKE = make

.PHONY: all clean

all: $(PROG)

# executable depends on object files
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

# object files depend on include files
indexer.o: $L/file.h $L/memory.h $L/webpage.h $C/pagedir.h $C/index.h

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
