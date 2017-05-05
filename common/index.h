/*
 * index.h - header file for CS50 index module
 *
 * Contains functionality to build index, save index to file, and
 * clean up index data strucuture.
 *
 * This module is used by indexer, indextest, and querier.
 *
 * Savannah Liu, April 2017
 */

#ifndef __index_H
#define __index_H

#include <stdio.h>
#include <stdbool.h>

/**************** global types ****************/
typedef struct index index_t;  // opaque to users of the module

/**************** functions ****************/

/* Builds index data structure from crawler output*/
index_t *index_build(char* pageDirectory, int num_slots);

/* save contents of index data structure into file called indexFilename */
void index_save(char *indexFilename, index_t index);

/* deletes index data structure */
void index_delete(index_t *index, void (*itemdelete)(void *item));


#endif // __index_H
