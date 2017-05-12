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

/* function prototype */
static bool parse_args(char* progName, char *pageDirectory, char *indexFilename);
static void querier(char *pageDirectory, char *indexFilename);
static bool blank_query(char *query);
static int tokenize_query(char *query, char *words[]);
static void validate_structure(char *words[], int wordCount);

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

  // read search queries from stdin, one per line, until EOF
  //while (feof(stdin) == 0){
  char *query;
  while((query = readlinep(stdin)) != NULL){   // read line, need to free this later

    if (blank_query(query) == false){ // proceed only if this query is not blank. if blank, ignore this query

      // calculate the max possible number of words (every character is separated by a space)
      // +1 because int division truncates towards zero
      int possiblewords = (strlen(query)/2) + 1;
      //printf("possible words: %d \n", possiblewords);

      char **words = count_malloc(possiblewords * sizeof(char *) + 1); // allocate memory for array of words, +1 to leave space for newline

      int wordCount = tokenize_query(query, words); // clean and parse query

      if(wordCount > 0){      // if it was not a bad query print cleaned query
        printf("clean query: ");
        for (int k=0; k < wordCount; k++){ //testing: print array
          printf("%s ", words[k]);
        }
        printf("\n");
      }

      // validate basic structure of query
      validate_structure(words, wordCount);

    }

  }
  //}

  // satisfy
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
static int tokenize_query(char *query, char *words[]){

  bool newWord = true;
  int i=0;    // query string index
  int j=0;    // words array index
  int wordCount=0; // number of words in array
  char *word; // pointer to beginning of word aka first letter
  char *rest; // pointer to end of word aka first non-letter, replace with null

  //char **word; // pointer to beginning of word aka first letter
//  char **rest; // pointer to end of word aka first non-letter, replace with null

  while( query[i] != '\0'){   // while not end of query
    if ((isspace(query[i]) == 0) && (isalpha(query[i]) == 0)){ // illegal character: not whitespace, not letter
      fprintf(stderr, "Error: bad character '%c' in query.\n", query[i]);
      return 0;
    }

    query[i] = tolower(query[i]); // normalize: convert to lowercase
    //printf("current char: %c\n", query[i]);

    if (newWord == true){     // looking for a new word
      //printf("new word\n");

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
        //printf("current word in array: %s\n", words[j]);

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
    //*rest = '\0';
    words[j] = word;  // add word to array
    wordCount++;
  }
  return wordCount;
}

/* validate basic structre of query - 'and' 'or' */
static void validate_structure(char *words[], int wordCount){
  int i;
  for (i=0; i<wordCount; i++){ // loop through words in array
    int cmpAnd = strcmp(words[i],"and");
    int cmpOr = strcmp(words[i],"or");

    // strcmp: return value 0 means strings are equal
    if((cmpAnd == 0) || (cmpOr == 0)){ // current word is 'and' or 'or'

      if(i==0) {  // it cannot be first word in query
        fprintf(stderr, "Error: '%s' cannot be first\n", words[i]);
      } else if(i == wordCount-1){ // cannot be last word in query
        fprintf(stderr, "Error: '%s' cannot be last\n", words[i]);
      } else{ // not the first or last word
        // check that adjacent (next) word is not 'and' or 'or'
        cmpAnd = strcmp(words[i+1],"and");
        cmpOr = strcmp(words[i+1],"or");
        if((cmpAnd == 0) || (cmpOr == 0)){
          fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n", words[i], words[i+1]);
        }
      }
    }
  }
}
