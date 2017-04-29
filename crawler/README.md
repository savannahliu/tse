# CS50 Tiny Search Engine (TSE) Crawler

Savannah Liu, April 2017.

## crawler
The TSE *crawler* is a standalone program that crawls the web and retrieves webpages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”.

## Usage
The *crawler* is implemented in `hashtable.c`

```c
/* Loops over pages to explore until list is exhausted uses bag to track pages to explore, hashtable tracks pages seen
 * when it explores a page it gives the page URL to the pagefetcher then the result to the pagesaver, then to the  
 * pagescanner
*/
void crawler(char *seedURL, char *pageDirectory, int maxDepth);

/* fetches the HTML of a page from a URL*/
bool pagefetcher(webpage_t *page);

/* outputs a page to the appropriate file: uses pagefetcher contents */
void pagesaver(webpage_t *page, int id, char *pageDirectory);

/* extracts URLs from a page and processes each one */
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag);

/* Used to print log - what URL has been fetched, added, saved, ignored, etc. */
inline static void logr(const char *word, const int depth, const char *url);

```

Arguments: an internal URL, a directory where you will output to, and the maximum depth to crawl to.
Example usage:
`./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth0/ 0`

## Assumptions
No assumptions beyond those that are clear from the spec.

## Compilation
To compile, simply `make`.
