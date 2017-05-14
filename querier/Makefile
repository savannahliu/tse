# Makefile for 'querier'
#
# Savannah Liu, May 2017
C = ../common
L = ../libcs50
PROG = querier
OBJS = querier.o
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
TEST_CRAWLERDIR = ../crawler/crawler-output/wikipedia/depth1
TEST_INDEXFILE = ../indexer/indexfile

.PHONY: all clean

all: $(PROG)

# object files depend on include files
querier.o: $L/file.h $L/memory.h $L/counters.h $L/hashtable.h $C/pagedir.h $C/index.h

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

################## bash script test ##################
test: querier testquery.sh
	./testquery.sh

###################### valgrind ######################
valgrind: querier
	$(VALGRIND) ./querier $(TEST_CRAWLERDIR) $(TEST_INDEXFILE) < testinput2.txt


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
