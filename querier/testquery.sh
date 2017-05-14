#!/bin/bash

# querier parameters
pageDirectory=../crawler/crawler-output/wikipedia/depth1
indexfile=../indexer/indexfile


# querier parameter tests ---------------------
echo
echo pageDirectory not a crawler directory
echo ./querier ../libcs50/ $indexfile
./querier ../libcs50/ $indexfile

echo
echo not a readable file
echo ./indexer $pageDirectory notreadable
./indexer $pageDirectory notreadable

# correct parameters, but queries with syntax errors ------------------

echo
echo queries with syntax errors
./querier $pageDirectory $indexfile < testinput1.txt


# queries with correct syntax -------------------------------

echo
echo test combining results and ranking
./querier $pageDirectory $indexfile < testinput2.txt

# Notes on textinput2.txt:

# explicit 'and'
# query: emili and bgu
# from indexfile:
# emili 7 1
# bgu 7 1
# expected output:
# score 1 doc 7

# implicit 'and'
# query: invoke tsch
# from indexfile:
# invoke 6 1
# tsch 5 1
# expected output:
# No matching documents

# 'or'
# query: kaling or entirely
# from indexfile:
# kaling 4 1
# entirely 4 1 7 1
# expected output:
# score 2 doc 4
# score 1 doc 7

# 'or' 'and'
# query: preferred and nir or ratio
# from indexfile:
# nir 3 1
# ratio 3 1
# preferred 3 1 4 1
# expected output:
# score 2 doc 3

# more docs - ranking
# query: include or enumerating or causes
# from indexfile:
# include 2 2 3 1 4 18 5 12 6 10 7 1
# enumerating 2 1
# causes 2 1  3 1  6 1
# expected output:
# score 18 doc 4
# score 12 doc 5
# score 11 doc 6
# score 4 doc 2
# score 2 doc 3
# score 1 doc 7


exit 0
