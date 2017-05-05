/*
 * indexer.h - header file for CS50 indexer module
 *
 * Creates indexer file from crawler output directory
 *
 * Savannah Liu, April 2017
 */

#ifndef __indexer_H
#define __indexer_H

#include <stdio.h>

/**************** functions ****************/

/* parses command line arguments */
bool parse_args(char* progName, char *pageDirectory, char *indexFilename);

/* creates the indexer data strcuture and indexer file */
void indexer(char *pageDirectory, char *indexFilename);


#endif // __indexer_H
