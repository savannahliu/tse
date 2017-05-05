/*
 * index.c - header file for CS50 index module
 *
 * see pagedir.h for more information.
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "hashtable.h"
#include "counters.h"
#include "webpage.h"
#include "set.h"
#include "memory.h"
#include "index.h"
#include "pagedir.h"
#include "word.h"
#include "file.h"

/**************** global types ****************/
typedef struct index {
  hashtable_t *ht;
} index_t;

/**************** local functions ****************/
/* not visible outside this file */
static void process_word(char *word, hashtable_t *ht, int fileid);
static char *create_crawlerfilename(int id, char *pageDirectory);

/**************** functions ****************/

/**************** index_build() ****************/
/* Builds index data structure from crawler output*/
index_t *
index_build(char* pageDirectory, int num_slots)
{
  hashtable_t *ht = hashtable_new(num_slots);
  // make a new filename: pageDirectory/id
  int id = 1;
  char *filename = create_crawlerfilename(id, pageDirectory);
  printf("filename: %s\n", filename);

  FILE *file;
  while((file = pageloader(filename)) != NULL){ // get files in pageDirectory

    //printf("index build while loop\n");
    char *url = readlinep(file); // get URL from first line of the file
    printf("url: %s\n", url);

    webpage_t *page = webpage_new(url, 0, NULL); // depth doesn't matter
    if (webpage_fetch(page) == false){ // get webpage using url webpage_fetch
      return NULL;  // error fetching page
    }
    int pos = 0;
    char *word;

    // get and process each word in the page (insert into index)
    while ((pos = webpage_getNextWord(page, pos, &word)) > 0){
      //printf("word: %s\n", word);
      if (strlen(word) > 2){  // make sure word is > 3 char and normalized
        //printf("word length ok - processing word \n");
        word = NormalizeWord(word);
        printf("normalized word: %s\n", word);
        process_word(word, ht, id);
      }
    }
    count_free(filename);
    fclose(file);
    id++; // update filename to next file
    filename = create_crawlerfilename(id, pageDirectory);
    printf("filename: %s\n", filename);


  }

  index_t *index = count_malloc(sizeof(index_t)); // hide ht data structure - make index struct
  if (index == NULL) {
    return NULL; // error allocating memory for node; return error
  } else {
    index->ht = ht;
  }
  return index;
}

/**************** process_word() ****************/
/* Processes words used in index_build()
 * Adds words into index
 */
static void
process_word(char *word, hashtable_t *ht, int fileid)
{
  counters_t *ctrs = counters_new(); // create new counter set
  if (hashtable_insert(ht, word, ctrs) == false){ // word already exists in index
    ctrs = hashtable_find(ht, word); // get the existing counter for the word
  }
  counters_add(ctrs, fileid);

  printf("counter: ");
  counters_print(ctrs, stdout); // testing
  printf("\n");
}

/**************** create_crawlerfilename() ****************/
/* appends int file id to pageDirectory to create a string filename
 * index_build is responsible for freeing memory for returned string
 */
static char *
create_crawlerfilename(int id, char *pageDirectory)
{
  char *idString = count_malloc(sizeof(char *));
  sprintf(idString, "/%d", id); // make id a string
  size_t length = strlen(idString) + strlen(pageDirectory) + 1;
  char *filename = count_malloc(sizeof(char *) * length + 1);
  strcpy(filename, pageDirectory);
  strcat(filename, idString);
  count_free(idString);
  return filename;
}

/**************** index_save() ****************/
/* save contents of index data structure into file called indexFilename */
void
index_save(char *indexFilename, index_t index)
{

}

/**************** index_delete() ****************/
/* deletes index data structure */
void
index_delete(index_t *index, void (*itemdelete)(void *item))
{
}
