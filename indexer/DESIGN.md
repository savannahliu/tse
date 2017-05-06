# Tiny Search Engine - indexer
# Design Spec

Savannah Liu May 2017

## Data Structure: Inverted index

Our index keeps track of words, which documents the words appear in, and how
many times a word appears in each document (later used to rank by querier).
The data structure indexer makes is an inverted index, which maps words to documents.

The inverted index is a hashtable, where keys are words and items are countersets.
(The hashtable is really a set, but allows for O(1) lookup time).
Each counterset node contains the id of a document (the key) and the count for
how many times the word appears in that document.

Indexer will use premade modules for hashtable and counterset.

## Indexer Pseudocode

Indexer will first process and validate command-line parameters.
Then indexer will build the inverted index data structure in a function
index_build(directory, index).

Indexer then saves index into a file using index_save(file, index). The file
is formatted so that there is one word per line. Each word is followed by
IDs of documents it appears in and the count.
Format of a line from the file: word docID count [docID count]...

Lastly, indexer cleans up data structures used.
