# Tiny Search Engine - querier
# Implementation Spec

Savannah Liu May 2017

This implementation of the TSE Querier is based on the Design Spec in
DESIGN.md and requirements provided in [Lab 6](http://www.cs.dartmouth.edu/~cs50/Labs/Lab6/REQUIREMENTS.html).

## Overall
We load an index from the indexFile given as a parameter to the program. We use it to look up queries read from stdin.

For each query, we parse the syntax then identify and score the documents that the words appear in. It then prints the
documents, ranking them in decreasing order.  

## Components
The code is divided amongst a few source files. `querier.c` contains the main function and many helper functions that do the bulk of the work. To handle counters and the hashtable, it makes use of modules in the libcs50 library. To handle loading files, validating the crawler directory, and loading the index, it uses modules in the common library.

### querier.c
```c
int main (const int argc, char *argv[])
```
is a short function that calls `parse_args` and `querier`, which does the main work.

----------------------------------------------------------
```c
static bool parse_args(char* progName, char *pageDirectory, char *indexFilename)
```
parses and validates parameters, exiting with non-zero status if there
is an error or parameters are wrong.   

----------------------------------------------------------
```c
static void querier(char *pageDirectory, char *indexFilename)
```
calls the functions `index_load` to load an index to use.

It reads queries from the stdin. It calls `blank_query` to recognize and ignore a blank query.
It calls `tokenize_query` then prints a clean query.

If there are no issues with the syntax of the query, it calls `validate_structure`.
If the structure of the query is ok, then it calls `satisfy_query` to get a counters_t that
contains the scored documents that satisfy the query.

It then ranks the documents by iterating the counters_t with the scored documents. Iterator uses`insert_docs`
to do insertion sort on an array. The array size is determined by iterating over the counters_t with the
helper function `count_docs`. Querier then prints these documents from the array in ranked order.

Lastly, it frees the memory and deletes the data structures.

----------------------------------------------------------

```c
static bool blank_query(char *query)
```
checks if the query is blank by checking if
entire string is just whitespace, used in querier.

----------------------------------------------------------
```c
static int tokenize_query(char *query, char *words[])
```
parses and cleans string query and populates an array of words using words in the string.
In the array of words, each slot will contain pointer to a word.

Checks for bad characters and returns number of words in the array.
----------------------------------------------------------
```c
static bool validate_structure(char *words[], int wordCount)
```
validates the structure of query. Specifically, 'and' and 'or' cannot be
adjacent, the first in the query, or the last in the query.

----------------------------------------------------------
```c
static counters_t* satisfy_query(char *words[], int wordCount, index_t *index)
```
returns counter set of documents that satisfy the query (sum of andsequences). It reads each word in
the words array and if it is not 'and' or 'or' it processes the word.

It calls `union_function` to do unions when it encounters an 'or'. If there is an 'and'
or an implicit 'and', it calls `satisfy_andseq` to build on an existing andsequence.

Calls `copy_ctrs` to copy a counters set from the index into a new andsequence to
avoid altering the original counter in index.
----------------------------------------------------------
```c
static void union_function(counters_t *andsequence, counters_t *query)
```
does a union with a andsequence and the query (aka the sum). It
calls `union_helper`.
----------------------------------------------------------
```c
static void union_helper(void *arg, const int key, int count)
```
helps `union_function` perform union.
----------------------------------------------------------
```c
static void satisfy_andseq(counters_t *andsequence, counters_t *word)
```
updates an andsequence with a new word.  It
  calls `intersection`.
----------------------------------------------------------
```c
static void intersection(void *arg, const int key, int count)
```
helps `satisfy_andseq` perform an intersection between
a word and an andsequence.
----------------------------------------------------------
```c
static void copy_ctrs(counters_t *andsequence, counters_t *word)
```
copies contents of a counterset into another. Calls `copy_ctrs_helper`.
----------------------------------------------------------
```c
static void copy_ctrs_helper(void *arg, const int key, int count)
```
is used by `copy_ctrs`.
----------------------------------------------------------
```c
static void count_docs(void *arg, const int key, int count)
```
counts number of items in the counters to determine size of array when ranking documents.
----------------------------------------------------------
```c
static void insert_docs(void *arg, const int key, int count)
```
used in ranking documents. Does insertion sort so that array will be in decreasing order (based on score).
