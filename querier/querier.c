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
#include "pagedir.h"
#include "index.h"
#include "counters.h"
#include "hashtable.h"

/* function prototype */
static bool parse_args(char* progName, char *pageDirectory, char *indexFilename);
static void querier(char *pageDirectory, char *indexFilename);
static bool blank_query(char *query);
static int tokenize_query(char *query, char *words[]);
static bool validate_structure(char *words[], int wordCount);
static counters_t* satisfy_query(char *words[], int wordCount, index_t *index);
static void union_function(counters_t *andsequence, counters_t *query);
static void union_helper(void *arg, const int key, int count);
static void satisfy_andseq(counters_t *andsequence, counters_t *word);
static void intersection(void *arg, const int key, int count);
static void copy_ctrs(counters_t *andsequence, counters_t *word);
static void copy_ctrs_helper(void *arg, const int key, int count);

//void counters_rank(counters_t *querydocs, struct satisfyingdoc *rankedArray);

//static int counters_rank(counters_t *querydocs);
static void count_docs(void *arg, const int key, int count);
static void insert_docs(void *arg, const int key, int count);

/**************** local types ****************/
struct twocounters {
  struct counters *andsequence;
  struct counters *otherset;
};

struct satisfyingdoc {
  int docID;
  int score;
};

struct rankingarray{
  struct satisfyingdoc **array; // array of satisfyingdoc structs
  int endindex;  // where an element should be inserted during insertion sort
  struct satisfyingdoc *doc;
};

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
    querier(pageDirectory, indexFilename);
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
  FILE *fp; // check that indexfilename is a readable file
  fp = fopen(indexFilename, "r");
  if(fp == NULL){
    fprintf(stderr, "error: %s is not readable\n", indexFilename);
    exit(3);
  }
  fclose(fp);
  return true;
}

/* Contains all logic for querier*/
static void
querier(char *pageDirectory, char *indexFilename)
{
  index_t *index = index_load(indexFilename); // load contents of indexfile into index data structure

  char *query;
  while((query = readlinep(stdin)) != NULL){   // read line, need to free this later
    if (blank_query(query) == false){ // proceed only if this query is not blank. if blank, ignore this query

      // calculate the max possible number of words (every character is separated by a space)
      // +1 because int division truncates towards zero
      int possiblewords = (strlen(query)/2) + 1;
      char **words = count_malloc(possiblewords * sizeof(char *) + 1); // allocate memory for array of words, +1 to leave space for newline
      int wordCount = tokenize_query(query, words); // clean and parse query

      if(wordCount > 0){      // if it was not a bad query print cleaned query
        printf("Entered: ");
        for (int k=0; k < wordCount; k++){ //testing: print array
          printf("%s ", words[k]);
        }
        printf("\n");
      }

      bool structureOk = validate_structure(words, wordCount); // validate basic structure of query
      if (structureOk == true){ // only continue processing this query if structure is sound, otherwise wait for next query

        counters_t *queryDocs = satisfy_query(words, wordCount, index); // satisfy

        int numItems = 0; // will determine array size
        counters_iterate(queryDocs, &numItems, count_docs); // count numItems

        if (numItems == 0){
          printf("No matching documents\n");
        } else{   //------------ Rank documents by score ---------------
          struct satisfyingdoc **rankedArray = count_malloc(numItems * sizeof(struct satisfyingdoc*)); // array of structs
          struct rankingarray *arraystruct = count_malloc(sizeof(struct rankingarray));
          arraystruct->array = rankedArray;
          arraystruct->endindex = 0; // start inserting here

          counters_iterate(queryDocs, arraystruct, insert_docs); // rank documents

          printf("Matches %d documents (ranked): \n", numItems);
          for(int i=0; i<numItems; i++){
            int score = rankedArray[i]->score; // http://stackoverflow.com/questions/18860123/invalid-type-argument-of©
            int docID = rankedArray[i]->docID;

            // make filename
            char *idString = count_malloc(sizeof(char *));
            sprintf(idString, "/%d", docID); // make id a string
            size_t length = strlen(idString) + strlen(pageDirectory) + 1; // http://stackoverflow.com/questions/5614411/correct-way-to-malloc-space-for-a-string-and-then-insert-characters-into-that-sp
            char *newfile = count_malloc(sizeof(char *) * length + 1);
            strcpy(newfile, pageDirectory);
            strcat(newfile, idString); // concatenate string https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm

            FILE *fp = fopen(newfile, "r");
            char *url = readlinep(fp); // get URL
            printf("score %d doc %d: %s", score, docID, url); // print out result
            printf("\n");

            count_free(idString);
            count_free(newfile);
            count_free(url);
            count_free(rankedArray[i]); // free the doc struct
          }

          count_free(arraystruct);
          count_free(rankedArray);
        }
        printf("\n");
        count_free(words); // free words array
        counters_delete(queryDocs); // free counter
      }

    }
    count_free(query); // free readlinep
  }
  index_delete(index);   // clean up data structures
}

/* checks if the query is just whitespace, used in querier */
static bool
blank_query(char *query){
  int i=0;
  while (query[i] != '\0'){
    if (isspace(query[i]) == 0){ // 0: there is a non-space char. not a blank line
      return false;
    }
    i++;
  }
  return true; // went through entire string and only found whitespace
}

/* parses and cleans string query and populates an array of words using words in the string*/
// in array of words, each slot will contain pointer to a word
static int
tokenize_query(char *query, char *words[]){

  bool newWord = true;
  int i=0;    // query string index
  int j=0;    // words array index
  int wordCount=0; // number of words in array
  char *word; // pointer to beginning of word aka first letter
  char *rest; // pointer to end of word aka first non-letter, replace with null

  while( query[i] != '\0'){   // while not end of query
    if ((isspace(query[i]) == 0) && (isalpha(query[i]) == 0)){ // illegal character: not whitespace, not letter
      fprintf(stderr, "Error: bad character '%c' in query.\n", query[i]);
      return 0;
    }
    query[i] = tolower(query[i]); // normalize: convert to lowercase

    if (newWord == true){     // looking for a new word
      if (isalpha(query[i]) != 0 ){  // it's a letter

        word = &(query[i]);  // pointer to the word
        rest = &(query[i]);     // pointer to the last read letter (end of word, as of now)
        newWord = false;      // we are no longer looking for the beginning of a word
      }
    } else { // not done reading a word
      rest = &(query[i]);

      if (isspace(*rest) != 0){ // its a space, which means the end of the word
        *rest = '\0';
        words[j] = word; // put the pointer to the word into the words array
        j++;             // increment index for words array
        wordCount++;
        newWord = true;
      }
    }
    i++; // increment index for query string
  }
  /* place last word - if got to end of line but did not place word in array
   because did not encounter a space to signal end of word */
  if (newWord == false){
    words[j] = word;  // add word to array
    wordCount++;
  }
  return wordCount;
}

/* validate basic structre of query - 'and' 'or'
used in querier */
static bool
validate_structure(char *words[], int wordCount){
  int i;
  for (i=0; i<wordCount; i++){ // loop through words in array
    int cmpAnd = strcmp(words[i],"and");
    int cmpOr = strcmp(words[i],"or");

    // strcmp: return value 0 means strings are equal
    if((cmpAnd == 0) || (cmpOr == 0)){ // current word is 'and' or 'or'

      if(i==0) {  // it cannot be first word in query
        fprintf(stderr, "Error: '%s' cannot be first\n", words[i]);
        return false;
      } else if(i == wordCount-1){ // cannot be last word in query
        fprintf(stderr, "Error: '%s' cannot be last\n", words[i]);
        return false;
      } else{ // not the first or last word
        // check that adjacent (next) word is not 'and' or 'or'
        cmpAnd = strcmp(words[i+1],"and");
        cmpOr = strcmp(words[i+1],"or");
        if((cmpAnd == 0) || (cmpOr == 0)){
          fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n", words[i], words[i+1]);
          return false;
        }
      }
    }
  }
  return true;
}

// -------------------------------

/* returns set of documents that satisfy the query */
static counters_t*
satisfy_query(char *words[], int wordCount, index_t *index){
  hashtable_t *ht = index_ht(index);
  bool newAndseq = true;
  counters_t *query = counters_new(); // sum. empty counter.
  counters_t *andseq;

  for(int i=0; i < wordCount; i++){ // for each word in the array

    // check if its a literal: 'and' 'or'
    int cmpAnd = strcmp(words[i],"and");
    int cmpOr = strcmp(words[i],"or");

    // strcmp: return value 0 means strings are equal
    if(cmpAnd == 0){        // its 'and'. do nothing. continue to next word
    //  printf("\n word: and\n");

    } else if(cmpOr == 0){  // it's 'or'
      // don't do anything with this word.
      newAndseq = true;         // start new andsequence on next word
      union_function(andseq, query);// union andseq with query
      counters_delete(andseq);  // delete the current andseq (so that if there is another one, we can start fresh)

    } else{               // regular word: not 'and' or 'or'

      if(newAndseq == true){ // start new andsequence
        counters_t *currentword = hashtable_find(ht, words[i]);

        andseq = counters_new(); // start with new andseq
        // copy this set into the andseq (so that we don't alter the original in the index)
        if (currentword != NULL){
          copy_ctrs(andseq, currentword);
        }
        newAndseq = false;

      } else{ // continue with current andsequence
        counters_t *currentword = hashtable_find(ht, words[i]);
        if (currentword != NULL){
          satisfy_andseq(andseq, currentword); // do intersection, updates andsequence ctrs

        }
      }
    }
  }
  union_function(andseq, query);// union andseq with query
  counters_delete(andseq);

  //counters_delete(andseq);  // delete the current andseq (so that if there is another one, we can start fresh)
  return query;
}

/* helper function used in satisfy_query.
* pass in two counters - one for andsequence and one for query
* updates query
*/
static void
union_function(counters_t *andsequence, counters_t *query){
  struct twocounters *bothctrs = malloc(sizeof(struct twocounters)); // make struct holding both ctrs so both can be passed to iterators
  bothctrs->andsequence = andsequence;
  bothctrs->otherset = query;
  // iterate over the andsequence
  counters_iterate(andsequence, bothctrs, union_helper); // args: counters_t *ctrs, void * arg, itemfunc
  count_free(bothctrs);
}

/* helper function used by union_function
* check to see if docs in andsequence appears in query counter
* update query by doing a union
* args: struct with counters, key in andsequence, count in andsequence
*/
static void
union_helper(void *arg, const int key, int count){
  struct twocounters *bothctrs = arg;
  int wordCtrsCount = counters_get(bothctrs->otherset, key);
  counters_set(bothctrs->otherset, key, wordCtrsCount+count); // update query with sum of counts
}

/* helper function used in satisfy_query.
* pass in two counters - one for andsequence and one for a word
* updates andsequence
*/
static void
satisfy_andseq(counters_t *andsequence, counters_t *word){
  struct twocounters *bothctrs = count_malloc(sizeof(struct twocounters)); // make struct holding both ctrs so both can be passed to iterators
  bothctrs->andsequence = andsequence;
  bothctrs->otherset = word;
  // iterate over the andsequence
  counters_iterate(andsequence, bothctrs, intersection); // args: counters_t *ctrs, void * arg, itemfunc
  count_free(bothctrs);
}

/* helper function used by satisfy_andseq
* check to see if docs in word ctrs appear in words ctrs
* update andsequence ctrs by doing an intersection
* args: struct with counters, key in andsequence, count in andsequence
*/
static void
intersection(void *arg, const int key, int count){
  struct twocounters *bothctrs = arg;
  int wordCtrsCount = counters_get(bothctrs->otherset, key);
  if (wordCtrsCount < count){ // update andsequence with minimum
    counters_set(bothctrs->andsequence, key, wordCtrsCount);
  }
}

/* helper function used in satisfy_query.
* pass in two counters - one for andsequence and one for a word
* copies a ctrs into andsequence to start new andsequence (so that we don't alter original ctrs in index)
*/
static void
copy_ctrs(counters_t *andsequence, counters_t *word){
  struct twocounters *bothctrs = count_malloc(sizeof(struct twocounters)); // make struct holding both ctrs so both can be passed to iterators
  bothctrs->andsequence = andsequence;
  bothctrs->otherset = word;
  // iterate over the andsequence
  counters_iterate(word, bothctrs, copy_ctrs_helper); // args: counters_t *ctrs, void * arg, itemfunc
  count_free(bothctrs);
}

/* helper function used by copy_ctrs
* copy ctrs item into andsequence
* args: struct with counters, key in andsequence, count in andsequence
*/
static void
copy_ctrs_helper(void *arg, const int key, int count){
  struct twocounters *bothctrs = arg;
  counters_set(bothctrs->andsequence, key, count);
}

// --------------------------------------------------------------------------------

/* count number of items in the counters to determine size of array in counters_rank */
static void
count_docs(void *arg, const int key, int count){
  if (count > 0){ // only count an item if its score is not 0
    int *numItems = arg;
    (*numItems)++;
  }
}

/*use insertion sort so that array will be in decreasing order (based on score) */
void
insert_docs(void *arg, const int key, int count){ // args: array of structs, key, count

  if (count > 0) {
    struct rankingarray *arraystruct = arg;
    struct satisfyingdoc *doc = count_malloc(sizeof(struct satisfyingdoc*)); // new

    arraystruct->doc = doc;  //new
    //struct satisfyingdoc *doc = arraystruct->doc;
    doc->docID = key;
    doc->score = count;

    struct satisfyingdoc **array = arraystruct->array;
    int index = arraystruct->endindex; // index starting point
    int i = index; // make copy of index starting point

    // insertion sort:
    array[i] = doc; // insert at end
    struct satisfyingdoc *temp = doc;   // make a struct that temporarily holds doc value during insertion

    // repeatedly compare with item on its left until reach the beginning of array or inserted:
    while (i > 0 && (temp->score > array[i-1]->score)){ // current item's score is greater than score of item on its left
      array[i] = array[i-1]; // slide over left item to current spot
      i--; // update index: go left
    }
    array[i] = temp; // insert item: current item's score is less than one on its left or reached index 0
    index++; // update the index where the next item should be inserted (end of array)
    arraystruct->endindex = index;
  }

}
