# CS50 Tiny Search Engine (TSE) Crawler Implementation Spec

Savannah Liu, April 2017.

### Implementation

We implement this crawler with a `main` function that parses the command line, validates parameters.
It makes sure there is the correct number of parameters. Then it checks if each parameter is correct: seedURL is checked to be internal with `IsInternalURL`, pageDirectory is checked to see if it exists and is writeable, and maxDepth must be a non-negative int. Then `main` calls a `crawler` function that does the actual work.

The `crawler` function initializes modules *hashtable* and *bag*. The hashtable holds the urls that we have already
visited to prevent us from visiting them again, and bag holds webpages we still need to explore. It makes a webpage for the seedURL, marked with depth=0, and adds that webpage to the bag of webpages to crawl. It also add that URL to the hashtable of URLs seen. Then there is a while loop that loops while there are more webpages we can extract from the bag. In this loop we extract a webpage (URL, depth) from the bag and calls `pagefetcher` to get a page for the extracted URL. It then calls `pagesaver`to write the webpage to the pageDirectory with a unique document ID.
If the webpage depth is < maxDepth, explore the webpage to find links. It calls `pagescanner` to parse the webpage to extract all its embedded URLs and processes them. The last things `crawler` does it delete the webpages, bag, and hashtable.

The `pagefetcher` function just calls webpage_fetch() on the page passed to it. This function is called by `crawler`.

The `pagesaver` outputs a page to a file in the pageDirectory. The filename is an int, which is passed to `pagesaver` from the `crawler` function.

The `pagescanner` parses the webpage to extract all its embedded URLs. It extracts each URL using webpage_getNextURL(). For each extracted URL it ‘normalizes’ the URL using NormalizeURL(). It also
ignores URLs that are considered not ‘internal’ by IsInternalURL(). It then uses hashtable_insert() to try to insert that URL into the hashtable of URLs seen. If hashtable_insert() did not add it to the table, that means it is already there so `pagescanner` does not do anything further with this URL. However, if it was added to the table,
make a new webpage for that URL using webpage_new(), at depth+1. It then adds the new webpage to the bag of webpages to be crawled.

The `logr` function that turns on print statements that appear inside crawler while it is processing URLs. These statements print a URL, its depth, and whether it was fetched, saved, scanned, found, ignored because it is a duplicate or external URL, or added. 
