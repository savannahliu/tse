Crawler Implementation Spec  - see lab 3 instructions as guide

Detailed pseudo code for each of the objects/components/functions,
main function:
Pseudo code for logic/algorithmic flow

The crawler will run as follows:

execute from a command line as shown in the User Interface

main() function:
The main function first parses the command line and validates the parameters.
It makes sure there is the correct number of parameters.
Then it checks if each parameter is correct: seedURL must be internal,
pageDirectory must exist and be writeable, and maxDepth must be a non-negative int.


It then initialize other modules, bag and hashtable.


make a webpage for the seedURL, marked with depth=0
add that page to the bag of webpages to crawl
add that URL to the hashtable of URLs seen

-------- 

while there are more webpages to crawl,
extract a webpage (URL,depth) item from the bag of webpages to be crawled,
pause for at least one second,
use pagefetcher to retrieve a webpage for that URL,
use pagesaver to write the webpage to the pageDirectory with a unique document ID, as described in the Requirements.
if the webpage depth is < maxDepth, explore the webpage to find links:
use pagescanner to parse the webpage to extract all its embedded URLs;
for each extracted URL,
‘normalize’ the URL (see below)
if that URL is not ‘internal’ (see below), ignore it;
try to insert that URL into the hashtable of URLs seen
if it was already in the table, do nothing;
if it was added to the table,
make a new webpage for that URL, at depth+1
add the new webpage to the bag of webpages to be crawled


Definition of detailed APIs, interfaces, function prototypes and their parameters,



Data structures (e.g., struct names and members),
Bag
Hashtable



Error handling and recovery,


Resource management,??



Persistant storage (files, database, etc).
