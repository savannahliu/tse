/*
 * pagedir.c - CS50 tse 'pagedir' module
 *
 * see pagedir.h for more information.
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "memory.h"
#include "webpage.h"

/**************** bag_new() ****************/
/* Check if given pageDirectory was produced by the crawler. */
bool
isCrawlerDirectory(char *pageDirectory)
{
  // if you can open pageDirectory/.crawler for reading then it is a crawler produced pageDirectoryectory
  char *filename;      // variable to hold pageDirectory/.crawler
  char * fileEnding;   // /.crawler
  FILE *fp;

  // concatenate .crawler to pageDirectory
  fileEnding = "/.crawler";
  size_t length = strlen(fileEnding) + strlen(pageDirectory) + 1;
  filename = count_malloc(sizeof(char *) * length + 1);
  strcpy(filename, pageDirectory);
  strcat(filename, fileEnding);

  fp = fopen(filename, "r");
  if (fp == NULL){ // not found. error: not a valid pathname, not a pageDirectoryectory, not readable, not produced by crawler, etc.
    count_free(filename);
    return false;
  } else { // if pageDirectory/.crawler is found, its a crawler pageDirectoryectory
    count_free(filename);
    fclose(fp);
    return true;
  }
}

/**************** pageloader() ****************/
/* Gives webpage of a file from crawler output pageDirectory */
FILE *
pageloader(char *file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL){ // error opening file
      return NULL;
    } else {
      fclose(fp);
      return fp;
    }
}

/**************** pagesaver() ****************/
/* outputs a page to the appropriate file: uses pagefetcher contents */
void
pagesaver(webpage_t *page, int id, char *pageDirectory)
{
  // make a new filename: in pageDirectory, with an int id
  char *idString = count_malloc(sizeof(char *));
  sprintf(idString, "%d", id); // make id a string
  size_t length = strlen(idString) + strlen(pageDirectory) + 1; // http://stackoverflow.com/questions/5614411/correct-way-to-malloc-space-for-a-string-and-then-insert-characters-into-that-sp
  char *newfile = count_malloc(sizeof(char *) * length + 1);
  strcpy(newfile, pageDirectory); // used for checking pageDirectory
  strcat(newfile, idString); // concatenate string https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm

  FILE *fp;
  fp = fopen(newfile, "w");
  fprintf(fp, "%s\n %d\n", webpage_getURL(page), webpage_getDepth(page)); // write URL and depth to the file
  fprintf(fp, "%s", webpage_getHTML(page));
  fclose(fp); // close the file
  count_free(newfile);
  count_free(idString);
}
