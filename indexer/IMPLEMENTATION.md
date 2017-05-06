# Tiny Search Engine - indexer
# Implementation Spec

Savannah Liu May 2017

This implementation of the TSE Indexer is based on the Design Spec in
DESIGN.md and requirements provided in [Lab 5](http://www.cs.dartmouth.edu/~cs50/Labs/Lab5/REQUIREMENTS.html).

## Overall
We use two data structures: a hashtable mapping words to counter sets. Each word's counter set holds IDs of documents that the word appears in, along with the count of how many times that word appears in the document.   

We first build the inverted index data structure using the files from the crawler output. We then use the contents of that index to write to a file.

## Components
The code is divided amongst a few source files. `indexer.c` contains the main function and uses modules in the common library to do the bulk of the work. `index.c` contains all the logic for building, saving, and deleting the index. `pagedir.c` contains the logic for loading file. `word.c` contains a function that normalizes words.

### indexer.c
```c
int main (const int argc, char *argv[])
```
is a short function that calls `parse_args` and `indexer`.

----------------------------------------------------------
```c
static bool parse_args(char* progName, char *pageDirectory, char *indexFilename)
```
parses and validates parameters, exiting with non-zero status if there
is an error or parameters are wrong.   

----------------------------------------------------------
```c
static void indexer(char *pageDirectory, char *indexFilename)
```
calls the functions `index_build` `index_save` `index_delete` in index.c that do most of the work building the index, saving the index, and deleting the index data structure.  

### index.c
Located in `../common` because it will be used by other parts of the tiny search engine.

```c
index_t *index_build(char* pageDirectory, int num_slots)
```
hides the data structures we are using to make the index. It creates a hashtable of counter sets using modules in `../libcs50`. It loads crawler output files using `pageloader` from `pagedir.c`.

To get the words in the webpages it uses `webpage.h` functions, then normalizes
the words using the `word.c` function `NormalizeWord`. It then calls a helper function called `process_word`, which inserts the word into the hashtable.

To hide the hashtable, `index_build` puts the hashtable inside an index
struct and returns this struct.

----------------------------------------------------------

```c
void index_save(char *indexFilename, index_t *index)
```
saves contents of index data structure into a file called indexFilename.
It passes in a local helperfunction `ht_print` into the `hashtable_iterate` function. `ht_print` then calls `counters_iterate`.

----------------------------------------------------------

```c
void index_delete(index_t *index)
```
deletes the index by passing a helper function `c_delete` to `hashtable_delete`. `c_delete`deletes the counters in the hashtable.   


### pagedir.c
Located in `../common` because it will be used by other parts of the tiny search engine.

```c
FILE *pageloader(char *file)
```
checks to see if given file is readable by trying to open it for reading.

----------------------------------------------------------
```c
bool isCrawlerDirectory(char *dir)
```
checks if the given directory is indeed a crawler produced directory. It does so by trying to open a file named ./crawler within the given directory.

### word.c
Located in `../common` because it will be used by other parts of the tiny search engine.

```c
char* NormalizeWord(char *word)
```
uses standard library function `tolower` to convert the given word to lowercase.
