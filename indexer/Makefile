# Makefile for 'indexer'
#
# Savannah Liu, May 2017
C = ../common
L = ../libcs50
PROG = indexer
OBJS = indexer.o
PROG2 = indextest
OBJS2 = indextest.o
LIBS = -lcurl
LLIBS = $C/common.a $L/libcs50.a # local libraries

# uncomment -DMEMTEST to turn on verbose memory logging
# run 'make clean; make' whenever you change this
FLAGS = #-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full 
TEST_CRAWLERDIR = /net/class/cs50/demo/crawler-output/cs50/depth0
TEST_INDEXFILE = indexfile

.PHONY: all clean

all: $(PROG) $(PROG2)

################## indexer ##########################
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

# object files depend on include files
indexer.o: $L/file.h $L/memory.h $L/webpage.h $C/pagedir.h $C/index.h

################## indextest #########################
$(PROG2): $(OBJS2) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS2) $(LLIBS) $(LIBS) -o $(PROG2)

indextest.o: $L/file.h $L/memory.h $C/pagedir.h $C/index.h

################## bash script test ##################
test: indexer indextest indextest.sh
	./indextest.sh

###################### valgrind ######################
valgrind: indexer
	$(VALGRIND) ./indexer $(TEST_CRAWLERDIR) $(TEST_INDEXFILE)


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f $(PROG2)
