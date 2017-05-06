/*
 * indextest.c- CS50 'indexer'
 *
 * usage:
 *   ./indextest oldIndexFilename newIndexFilename
 * where oldIndexFilename is the name of a file produced by the indexer
 * and newIndexFilename is the name of a file into which the indextest should be written
 *
 * Savannah Liu, May 2017
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "file.h"
#include "memory.h"
#include "pagedir.h"
#include "index.h"

/* function prototypes */
static bool parse_args(char* progName, char *oldIndexFilename, char *newIndexFilename);

/* main function */
int main (const int argc, char *argv[]) {
  char *progName = argv[0];   // name of this program
  char *oldIndexFilename = argv[1];
  char *newIndexFilename = argv[2];

  if (argc > 3) {
    fprintf(stderr, "usage: incorrect number of arguments\n");
    exit(1);
  }

  if (parse_args(progName, oldIndexFilename, newIndexFilename) == true){
    index_t *index = index_load(oldIndexFilename);
    index_save(newIndexFilename, index);
    index_delete(index);
  }
  //count_report(stdout, "count report: ");
}

/* parse and validate command line arguments */
static bool
parse_args(char* progName, char *oldIndexFilename, char *newIndexFilename)
{
  // check that oldIndexFilename is readable
  FILE *fp;
  fp = fopen(oldIndexFilename, "r");
  if(fp == NULL){
    fprintf(stderr, "error: %s is not readable\n", oldIndexFilename);
    exit(2);
  }
  fclose(fp);

  // create a newIndexFilename - make sure it's writeable
  fp = fopen(newIndexFilename, "w");
  if(fp == NULL){
    fprintf(stderr, "error: %s is not readable\n", newIndexFilename);
    exit(3);
  }
  fclose(fp);

  return true;
}
