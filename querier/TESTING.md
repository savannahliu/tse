# CS50 Tiny Search Engine (TSE) Querier Testing Documentation

Savannah Liu, May 2017.

This implementation of the TSE Querier is based on the Design Spec in
DESIGN.md and requirements provided in [Lab 6](http://www.cs.dartmouth.edu/~cs50/Labs/Lab6/REQUIREMENTS.html).

In this document we describe our approach to testing and the
results of the testing.

## Makefile

We wrote a phony rule `test` in the Makefile. It depends on `querier` and `testquery.sh`. It simply executes `testquery.sh`.

We wrote a phony rule `valgrind` in the Makefile. It depends on `querier`. It runs a few different queries so we can look for memory errors or leaks.

## testquery.sh

This bash script creates a few indexfile and testresult files and removes any existing directories that may be left from a prior run.

It first tests `querier` with variety of bad commandline parameters.

It then tests queries with bad syntax.

It then tests queriers with correct syntax. It tests combining and ranking results.


## Test run
```
[sav@moose ~/cs50/labs/lab4/tse/querier]$ make test
./testquery.sh

pageDirectory not a crawler directory
./querier ../libcs50/ ../indexer/indexfile
usage: ./querier pageDirectory must be a readable crawler produced directory

not a readable file
./indexer ../crawler/crawler-output/wikipedia/depth1 notreadable
./testquery.sh: line 17: ./indexer: No such file or directory

queries with syntax errors
Query: and
Error: 'and' cannot be first
Query: or
Error: 'or' cannot be first
Query: and dartmouth
Error: 'and' cannot be first
Query: or dartmouth
Error: 'or' cannot be first
Query: dartmouth college or
Error: 'or' cannot be last
Query: dartmouth college and
Error: 'and' cannot be last
Query: dartmouth college and or computer
Error: 'and' and 'or' cannot be adjacent
Query: dartmouth college and and computer
Error: 'and' and 'and' cannot be adjacent
Query: dartmouth college or and computer
Error: 'or' and 'and' cannot be adjacent
Error: bad character '5' in query.
Error: bad character '!' in query.
Error: bad character '-' in query.

test combining results and ranking
Query: emili and bgu
Matches 1 documents (ranked):
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

Query: invoke tsch
No matching documents

Query: kaling or entirely
Matches 2 documents (ranked):
score 2 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

Query: preferred and nir or ratio
Matches 1 documents (ranked):
score 2 doc 3: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html

Query: include or enumerating or causes
Matches 6 documents (ranked):
score 18 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 12 doc 5: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
score 11 doc 6: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
score 4 doc 2: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
score 2 doc 3: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

[sav@moose ~/cs50/labs/lab4/tse/querier]$ 
```

## Valgrind tests
```
[sav@moose ~/cs50/labs/lab4/tse/querier]$ make valgrind
gcc -Wall -pedantic -std=c11 -ggdb  -I../libcs50 -I../common   -c -o querier.o querier.c
gcc -Wall -pedantic -std=c11 -ggdb  -I../libcs50 -I../common querier.o ../common/common.a ../libcs50/libcs50.a  -lcurl -o querier
valgrind --leak-check=full ./querier ../crawler/crawler-output/wikipedia/depth1 ../indexer/indexfile < testinput2.txt
==13666== Memcheck, a memory error detector
==13666== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==13666== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==13666== Command: ./querier ../crawler/crawler-output/wikipedia/depth1 ../indexer/indexfile
==13666==
Query: emili and bgu
Matches 1 documents (ranked):
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

Query: invoke tsch
No matching documents

Query: kaling or entirely
Matches 2 documents (ranked):
score 2 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

Query: preferred and nir or ratio
Matches 1 documents (ranked):
score 2 doc 3: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html

Query: include or enumerating or causes
Matches 6 documents (ranked):
score 18 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 12 doc 5: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
score 11 doc 6: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
score 4 doc 2: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
score 2 doc 3: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

==13666==
==13666== HEAP SUMMARY:
==13666==     in use at exit: 5,520 bytes in 10 blocks
==13666==   total heap usage: 45,223 allocs, 45,213 frees, 13,697,346 bytes allocated
==13666==
==13666== LEAK SUMMARY:
==13666==    definitely lost: 0 bytes in 0 blocks
==13666==    indirectly lost: 0 bytes in 0 blocks
==13666==      possibly lost: 0 bytes in 0 blocks
==13666==    still reachable: 5,520 bytes in 10 blocks
==13666==         suppressed: 0 bytes in 0 blocks
==13666== Reachable blocks (those to which a pointer was found) are not shown.
==13666== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==13666==
==13666== For counts of detected and suppressed errors, rerun with: -v
==13666== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
[sav@moose ~/cs50/labs/lab4/tse/querier]$

```
