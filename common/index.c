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
static void ht_print(void *arg, const char *key, void *item);
static void ctrs_print(void *arg, const int key, int count);
static void c_delete(void *item);

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
    char *url = readlinep(file); // get URL from first line of the file

    webpage_t *page = webpage_new(url, 0, NULL); // depth doesn't matter
    if (webpage_fetch(page) == false){ // get webpage using url webpage_fetch
      return NULL;  // error fetching page
    }
    int pos = 0;
    char *notNormalizedWord;
    char *word;

    // get and process each word in the page (insert into index)
    while ((pos = webpage_getNextWord(page, pos, &notNormalizedWord)) > 0){
      if (strlen(notNormalizedWord) > 2){  // make sure word is > 3 char and normalized
        word = NormalizeWord(notNormalizedWord);
        process_word(word, ht, id);
        count_free(word);
      }
      free(notNormalizedWord);
    }
    count_free(filename);
    webpage_delete(page);
    free(url);

    fclose(file);
    id++; // update filename to next file
    filename = create_crawlerfilename(id, pageDirectory);
  //  printf("filename: %s\n", filename);
  }
  count_free(filename);

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
    free(ctrs);
    ctrs = hashtable_find(ht, word); // get the existing counter for the word
  }
  counters_add(ctrs, fileid);
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
index_save(char *indexFilename, index_t *index)
{
  FILE *fp;
  fp = fopen(indexFilename, "w");
  hashtable_iterate(index->ht, fp, ht_print); // parameters: ht, file, helper function
  fclose(fp); // close the file
}

/**************** ht_print() ****************/
/* helper function used in index_save
*  (prints a line in format: word docID count [docID count]...)
* prints the word, calls ctrs_print to print docID count...
*/
static void
ht_print(void *arg, const char *key, void *item)
{
  // prints word to file
  fprintf(arg, "%s ", key);
  counters_iterate(item, arg, ctrs_print); // parameters: ctrs, file, helper function
  fprintf(arg, "\n"); // end of line
}

/**************** ctrs_print() ****************/
/* helper function used in in index_save
* prints docid count ...
*/
static void
ctrs_print(void *arg, const int key, int count)
{
  fprintf(arg, "%d %d ", key, count); // docID and count
}

/**************** index_delete() ****************/
/* deletes index data structure */
void
index_delete(index_t *index)
{
  hashtable_delete(index->ht, c_delete);
  count_free(index);
}

/**************** c_delete() ****************/
/* helper function used in index_delete
* deletes counters
*/
static void
c_delete(void *item)
{
  counters_delete(item); // pass it a ctrs to delete
}

/**************** index_load() ****************/
/* load contents of index file into index data structure */
index_t *
index_load(char *indexFilename)
{

  FILE *file;
  if ((file = pageloader(indexFilename)) == NULL){ // get indexFile
    return NULL;
  }

  int num_slots = lines_in_file(file); // number of slots is number of words: one word per line
  hashtable_t *ht = hashtable_new(num_slots); // make hashtable

  //char *word = count_malloc(sizeof(char *)+1);
  char *word; // holds word index_load is currently scanning
  //while (fscanf(file, "%s ", word) == 1){ // while not end of file & successfully scan word

  while ((word = readwordp(file)) != NULL){ // while not end of file

    counters_t *ctrs = counters_new(); // create new counter set for current word
    int docID;
    int count;

    while (fscanf(file, "%d %d ", &docID, &count) == 2) { // read until end of line
        counters_add(ctrs, docID); // add docID into counter f or current word
        counters_set(ctrs, docID , count); // set it to count
    }

    hashtable_insert(ht, word, ctrs); // insert counter into ht
    free(word);
  }
  //count_free(word);
  fclose(file);

  index_t *index = count_malloc(sizeof(index_t)); // hide ht data structure - make index struct
  if (index == NULL) {
    return NULL; // error allocating memory for node; return error
  } else {
    index->ht = ht;
  }
  return index;

}
