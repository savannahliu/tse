# Makefile for common library
#   Builds and compiles all these utility functions into a library.
#
# based on libcs50 makefile by David Kotz, April 2016, 2017, updated by Xia Zhou, July 2016
# Savannah Liu May 2017

# object files, and the target library
L = ../libcs50
OBJS = pagedir.o index.o word.o
LIB = common.a

# add -DNOSLEEP to disable the automatic sleep after web-page fetches
#               (students, please do not use -DNOSLEEP!)
# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DNOSLEEP # -DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L
CC = gcc
MAKE = make

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files

pagedir.o: pagedir.h $L/file.h $L/memory.h $L/webpage.h
index.o: index.h $L/counters.h $L/hashtable.h $L/webpage.h $L/set.h $L/memory.h $L/file.h pagedir.h word.h
word.o: word.h $L/memory.h


.PHONY: clean sourcelist

# list all the sources and docs in this directory.
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o
