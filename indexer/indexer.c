/*
 * indexer.c- CS50 'indexer'
 *
 * usage:
 *   indexer pageDirectory indexFilename
 * where pageDirectory is a pathname for a directory created by the crawler,
 * and indexFilename is a file into which the index should be written
 *
 * for example: indexer ./pgDir/ indexfile
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <ctype.h> // used for isdigit
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "indexer.h"
#include "file.h"
#include "memory.h"
#include "webpage.h"
#include "pagedir.h"
#include "index.h"

const int INDEX_SIZE = 200;

/* main function */
int main (const int argc, char *argv[]) {
  char *progName = argv[0];   // name of this program
  char *pageDirectory = argv[1];
  char *indexFilename = argv[2];

  if (parse_args(progName, pageDirectory, indexFilename) == true){
    indexer(pageDirectory, indexFilename);
  }
}

/* parse and validate command line arguments */
bool
parse_args(char* progName, char *pageDirectory, char *indexFilename)
{
  // directory is not crawler directory or has some other issue (like not readable)
  if (isCrawlerDirectory(pageDirectory) == false){
    fprintf(stderr, "usage: %s pageDirectory must be a crawler produced directory\n", progName);
    exit(1);
  }
  // make a writeable file called indexFilename (overwrite if it already exists)
  FILE *fp;
  fp = fopen(indexFilename, "w+");
  if(fp == NULL){
    fprintf(stderr, "error: %s is not writeable\n", indexFilename);
    exit(2);
  }
  fclose(fp);
  return true;
}

/* Contains all logic for creating index*/
void
indexer(char *pageDirectory, char *indexFilename)
{
  // build index
  printf("building index\n"); 
  index_t *index = index_build(pageDirectory, INDEX_SIZE);

  // save index in indexFilename
  // index_save(indexfilename, index);

  // clean up data structures
  // delete_index();
}
