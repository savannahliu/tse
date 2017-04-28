/*
 * crawler.c - CS50 'crawler'
 *
 * usage:
 *   crawler seedURL pageDirectory maxDepth
 * where seedURL is used as the original URL, pageDirectory is a pathname for
 * an existing directory in which to write downloaded webpages, and
 * maxDepth is a non-negative integer representing the maximum crawl depth
 *
 * for example: crawler http://old-www.cs.dartmouth.edu/index.html ./pgDir/ 2
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <ctype.h> // used for isdigit
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "file.h"
#include "memory.h"
#include "bag.h"
#include "hashtable.h"
#include "webpage.h"

const int HT_NUM_SLOTS = 100;
char * HT_ITEM = "htitem"; // item stored in ht

/* function prototypes */
void crawler(char *seedURL, char *pageDirectory, int maxDepth);
bool pagefetcher(webpage_t *page);
void pagesaver(webpage_t *page, int id, char *pageDirectory);
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag);


//static void bagitemprint(FILE *fp, void *item);
//static void htitemprint(FILE *fp, const char *key, void *item);

/* main function
* parses arguments and initializes other modules
*/
int main (const int argc, char *argv[]) {
  char *progName = argv[0];   // name of this program
  char *seedURL;
  char *pageDirectory;
  FILE *fp;                   // used for checling pageDirectory
  char * fileEnding;          // used for checling pageDirectory
  char *maxDepthString;       // used for checking if maxDepth is int
  int maxDepth;

  // parse arguments and validate parameters ----------------------------------
  if (argc != 4) { // check for number of arguments
    fprintf(stderr, "usage: %s seedURL pageDirectory maxDepth\n", progName);
    exit(1);
  }

  // correct number of arguments
  seedURL = argv[1];
  pageDirectory = argv[2];

  // check URL is internal aka within CS50 playground http://old-www.cs.dartmouth.edu/
  if (IsInternalURL(seedURL) == false){
    fprintf(stderr, "usage: %s seedURL must be internal\n", progName);
    exit(2);
  }

  // check pageDirectory exists and is writeable - make a new file called pgDir/.crawler
  // for strcpy need to allocate space for null char http://stackoverflow.com/questions/27636306/valgrind-address-is-0-bytes-after-a-block-of-size-8-allocd
  fileEnding = ".crawler";
  size_t length = strlen(fileEnding) + strlen(pageDirectory) + 1; // http://stackoverflow.com/questions/5614411/correct-way-to-malloc-space-for-a-string-and-then-insert-characters-into-that-sp
  char *filename = count_malloc(sizeof(char *) * length + 1);
  strcpy(filename, pageDirectory);
  strcat(filename, fileEnding); // concatenate string https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm

  fp = fopen(filename, "w");
  if (fp == NULL){
    fprintf(stderr, "usage: %s does not exist or is not writeable\n", pageDirectory);
    exit(3); // does not exist or is not writeable
  } else {
    fclose(fp); // success. close file
  }

  maxDepthString = argv[3];
  if (sscanf(maxDepthString, "%d", &maxDepth) != 1 || maxDepth < 0) { // maxDepth not integer (char or float)
    fprintf(stderr, "usage: maxDepth must be a non-negative integer\n");
    exit(4);
  }
  count_free(filename);
  //count_free(fileEnding);

  // initialize other modules  --------------------------------------------
  crawler(seedURL, pageDirectory, maxDepth);

  count_report(stdout, "count report! ");
}

/* Loops over pages to explore until list is exhausted uses bag to track pages to explore, hashtable tracks pages seen
 * when it explores a page it gives the page URL to the pagefectcher then the result to the pagesaver, then to the pagescanner
*/
void crawler(char *seedURL, char *pageDirectory, int maxDepth){
  bag_t *bag;   // create bag of webpages to crawl
  bag = bag_new();
  if (bag == NULL) {
    fprintf(stderr, "bag_new failed\n");
    exit(5);
  }

  hashtable_t *ht;   // create hashtable of webpages seen
  ht = hashtable_new(HT_NUM_SLOTS);
  if (ht == NULL) {
    fprintf(stderr, "hashtable_new failed\n");
    exit(6);
  }

  webpage_t *page;  // create first page struct for seedURL
  page = webpage_new(seedURL, 0, NULL);
  bag_insert(bag, page);
  hashtable_insert(ht, seedURL, HT_ITEM);

  int id = 1;
  while ((page = bag_extract(bag)) != NULL) { // while bag is not empty: there are more webpages to crawl

    if (pagefetcher(page) == true) { // pause for a second & use pagefetcher to get a webpage for the URL
      pagesaver(page, id, pageDirectory); // write webpage to pageDirectory with unique doc id
      id++; // update id for next document
      if (webpage_getDepth(page) < maxDepth){ // if webpage depth is less than maxdepth, explore the webpage for links
        pagescanner(page, ht, bag);
      }
    }
    webpage_delete(page);
  }
  // delete the bag
  bag_delete(bag, webpage_delete);
  hashtable_delete(ht, NULL);
}

/* fetches the HTML of a page from a URL*/
bool pagefetcher(webpage_t *page){
  return webpage_fetch(page);
}

//outputs a page to the appropriate file: uses pagefetcher contents
void pagesaver(webpage_t *page, int id, char *pageDirectory){
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

/*
  sprintf(pageDirectory, "%s%d", pageDirectory, id); // creates add id to filename by appending to pageDirectory
  FILE *fp;
  fp = fopen(pageDirectory, "w");
  fprintf(fp, "%s\n %d\n", webpage_getURL(page), webpage_getDepth(page)); // write URL and depth to the file
  fprintf(fp, "%s", webpage_getHTML(page));
  fclose(fp); // close the file
  */
}


/* extracts URLs from a page and processes each one*/
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag){
  // parse webpage to extract all URLS
  int depth = webpage_getDepth(page);
  depth++;
  int pos = 0;   // position in the HTML
  char *result;  // URL retreived

  // write the html of the webpage to the file in pageDirectory
  while ((pos = webpage_getNextURL(page, pos, &result)) > 0){ // while you have not run out of HTML
    // store next URL in the html into result. update position
    if (NormalizeURL(result) == true) { // normalize the url
      if (IsInternalURL(result) == true){ // ignore non-internal links
        if (hashtable_insert(ht, result, HT_ITEM) == true){ // insert into ht
          webpage_t *page; // make a new webpage at depth + 1 if inserted
          page = webpage_new(result, depth, NULL);
          bag_insert(bag, page);
        }
      }
    }
    count_free(result);
  }
}


// Testing functions -----------------------------------------------------

/*Prints out a webpage bag item (url, depth, html) for testing purposes.
static void bagitemprint(FILE *fp, void *item){
  if (fp != NULL && item != NULL)
    fprintf(fp, "page: url %s, depth %d\n", webpage_getURL(item), webpage_getDepth(item));
}

Prints out a webpage ht item (url, depth, html) for testing purposes.
static void htitemprint(FILE *fp, const char *key, void *item){
  char *string = item;
  if (fp != NULL && key != NULL && item != NULL)
  fprintf(fp, "URL key: %s, const string item %s\n", key, string);
}
*/
