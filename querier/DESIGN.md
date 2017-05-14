# Tiny Search Engine - querier
# Design Spec

Savannah Liu May 2017

## Data Structures:

The querier uses an index, which is really a hashtable of counter sets.
The querier uses also counter sets to combine and score query results.
To rank results, querier uses an array.

Querier uses premade modules for hashtable and counterset.

## Querier Pseudocode

Querier first processes and validates command-line parameters. It then
loads the index from the indexFilename given as a command-line parameter.

The program reads search queries from stdin, one per line, until EOF. It ignores blank lines.
For each search query, it parses the syntax so that the literals 'and' and 'or' only appear between other words. It gives errors if there are syntax errors (i.e. numbers, punctuation, adjacent literals).

It then prints a clean, normalized query for the user to see.

Next it uses the index to identify a set of documents that satisfy the query. If no documents match, it tells the user.

If there are matching documents, it scores the documents based on the count stored for that docID. The literals 'and' and 'or'
also affect the score, with 'and' having precedence over 'or'. 
It then prints the documents out in decreasing rank order. Each documents's score, docID, and url is printed.

Lastly, querier cleans up data structures used.
