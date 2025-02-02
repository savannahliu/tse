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
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "file.h"
#include "memory.h"
#include "webpage.h"
#include "pagedir.h"
#include "index.h"

const int INDEX_SIZE = 200;

/* function prototype */
static bool parse_args(char* progName, char *pageDirectory, char *indexFilename);
static void indexer(char *pageDirectory, char *indexFilename);

/* main function */
int main (const int argc, char *argv[]) {
  char *progName = argv[0];   // name of this program
  char *pageDirectory = argv[1];
  char *indexFilename = argv[2];

  if (argc != 3) {
    fprintf(stderr, "usage: incorrect number of arguments\n");
    exit(1);
  }

  if (parse_args(progName, pageDirectory, indexFilename) == true){
    indexer(pageDirectory, indexFilename);
  }
  //count_report(stdout, "count report: ");
}

/* parse and validate command line arguments */
static bool
parse_args(char* progName, char *pageDirectory, char *indexFilename)
{
  // directory is not crawler directory or has some other issue (like not readable)
  if (isCrawlerDirectory(pageDirectory) == false){
    fprintf(stderr, "usage: %s pageDirectory must be a readable crawler produced directory\n", progName);
    exit(2);
  }
  // make a writeable file called indexFilename (overwrite if it already exists)
  FILE *fp;
  fp = fopen(indexFilename, "w+");
  if(fp == NULL){
    fprintf(stderr, "error: %s is not writeable\n", indexFilename);
    exit(3);
  }
  fclose(fp);
  return true;
}

/* Contains all logic for creating index*/
static void
indexer(char *pageDirectory, char *indexFilename)
{
  index_t *index = index_build(pageDirectory, INDEX_SIZE);  // build index
  index_save(indexFilename, index); // save index in indexFilename
  index_delete(index);   // clean up data structures
}
