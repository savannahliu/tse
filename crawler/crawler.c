/*
 * crawler.c - CS50 'crawler'
 *
 * usage:
 *   crawler seedURL pageDirectory maxDepth
 * where seedURL is used as the original URL, pageDirectory is a pathname for
 * an existing directory in which to write downloaded webpages, and
 * maxDepth is a non-negative integer representing the maximum crawl depth
 *
 * for example: crawler http://old-www.cs.dartmouth.edu/index.html ./data/ 2
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

// webpage items that go into bag: contains url and depth
struct page {
  char *url;
  int depth;
}

const int HT_NUM_SLOTS = 100;
const char * HT_ITEM = "ht item"; // item stored in ht

/* function prototypes */
void crawler(char *seedURL, char *pageDirectory, int maxDepth);
//webpage_t *pagefetcher(char *url, const int depth, char *html);
//void pagesaver();
//void pagescanner(hashtable, bag, URL, depth);

/* main function
* parses arguments and initializes other modules
*/
int main (const int argc, char *argv[]) {
  char *progName = argv[0];   // name of this program
  char *seedURL;
  char *pageDirectory;
  char *fileEnding;            // used for checking pageDirectory
  FILE *fp;                   // used for checling pageDirectory
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
  char *filename = count_malloc(sizeof(char *));;  // used for checking pageDirectory
  strcpy(filename, pageDirectory);
  maxDepthString = argv[3];

  // check URL is internal aka within CS50 playground http://old-www.cs.dartmouth.edu/
  if (IsInternalURL(seedURL) == false){
    fprintf(stderr, "usage: %s seedURL must be internal\n", progName);
    exit(2);
  }

  // check pageDirectory exists and is writeable
  fileEnding = ".crawler";
  strcat(filename, fileEnding); // concatenate string https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm
  // concatenate .crawler onto pageDirectory to make a new filename
  fp = fopen(filename, "w");
  if (fp == NULL){
    fprintf(stderr, "usage: %s does not exist or is not writeable\n", pageDirectory);
    exit(3); // does not exist or is not writeable
  } else {
    fclose(fp); // success. close file
  }

  if (sscanf(maxDepthString, "%d", &maxDepth) != 1 || maxDepth < 0) { // maxDepth not integer (char or float)
    fprintf(stderr, "usage: maxDepth must be a non-negative integer\n");
    exit(4);
  }

  count_free(filename);

  // initialize other modules  --------------------------------------------

}

/* Loops over pages to explore until list is exhausted
 * uses bag to traack pages to explore, hashtable tracks pages seen
 * when it explores a page it gives the page URL to the pagefectcher
 * then the result to the pagesaver, then to the pagescanner
*/
void crawler(char *seedURL, char *pageDirectory, int maxDepth){
  // create bag of webpages to crawl
  bag_t *bag;
  bag = bag_new();
  if (bag == NULL) {
    fprintf(stderr, "bag_new failed\n");
    exit(5);
  }

  // create hashtable of webpages seen
  hashtable_t *ht;
  ht = hashtable_new(HT_NUM_SLOTS);
  if (ht == NULL) {
    fprintf(stderr, "hashtable_new failed\n");
    exit(6);
  }

  // create first page struct for seedURL
  struct page *pg = count_malloc(sizeof(struct page));
  pg->url = seedURL;
  pg->depth = 0;
  bag_insert(bag, pg);
  hashtable_insert(ht, pg->URL, HT_ITEM);

  while (pg = bag_extract(bag) != NULL){ // while bag is not empty: there are more webpages to crawl
    char * url = pg->url;

    

  }
}


/* fetches the HTML of a page from a URL
webpage_t *pagefetcher(char *url, const int depth, char *html){
}
*/

/* outputs a page to the appropriate file: uses pagefetcher contents
void pagesaver(char *url, const int depth, html from pagefetcher?, const *filename){
}
*/

/* extracts URLs from a page and returns one at a time ???
webpage_t *pagefetcher(html from pagefetcher?){
}
*/
