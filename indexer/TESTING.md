# CS50 Tiny Search Engine (TSE) Indexer Testing Documentation

Savannah Liu, May 2017.

This implementation of the TSE Indexer is based on the Design Spec in
DESIGN.md and requirements provided in [Lab 5](http://www.cs.dartmouth.edu/~cs50/Labs/Lab5/REQUIREMENTS.html).

In this document we describe our approach to testing and the
results of the testing.

## Makefile

We wrote a phony rule `test` in the Makefile. It depends on `indexer`, `indextest`, and `indextest.sh`. It simply executes `indextest.sh`.

We wrote a phony rule `valgrind` in the Makefile. It depends on `indexer`. It runs a single test of `indexer` so we can look for memory errors or leaks.

## indextest.sh

This bash script creates a few indexfile and testresult files and removes any existing directories that may be left from a prior run.

It first tests `indexer` with variety of bad commandline parameters.

The script then runs `indexer` and `indextest` at 4 different depths using
crawler output from /net/class/cs50/demo/crawler-output/cs50/.


## Test run
```
[sav@moose ~/cs50/labs/lab4/tse/indexer]$ make test
./indextest.sh

isnt a directory
usage: ./indexer pageDirectory must be a readable crawler produced directory

isnt a crawler directory
usage: ./indexer pageDirectory must be a readable crawler produced directory

not readable directory
usage: ./indexer pageDirectory must be a readable crawler produced directory

indexer depth 0

indextest depth 0

sort and compare: indexfile0 testresult0
success! no differences

indexer depth 1

indextest depth 1

sort and compare: indexfile1 testresult1
success! no differences

indexer depth 2

indextest depth 2

sort and compare: indexfile2 testresult2
success! no differences

indexer depth 3

indextest depth 3

sort and compare: indexfile3 testresult3
success! no differences
```

## Valgrind tests
```
[sav@moose ~/cs50/labs/lab4/tse/indexer]$ make valgrind
valgrind --leak-check=full  ./indexer /net/class/cs50/demo/crawler-output/cs50/depth0 indexfile
==13461== Memcheck, a memory error detector
==13461== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==13461== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==13461== Command: ./indexer /net/class/cs50/demo/crawler-output/cs50/depth0 indexfile
==13461==
==13461==
==13461== HEAP SUMMARY:
==13461==     in use at exit: 24,253 bytes in 655 blocks
==13461==   total heap usage: 1,114 allocs, 459 frees, 2,304,033 bytes allocated
==13461==
==13461== LEAK SUMMARY:
==13461==    definitely lost: 0 bytes in 0 blocks
==13461==    indirectly lost: 0 bytes in 0 blocks
==13461==      possibly lost: 0 bytes in 0 blocks
==13461==    still reachable: 24,253 bytes in 655 blocks
==13461==         suppressed: 0 bytes in 0 blocks
==13461== Reachable blocks (those to which a pointer was found) are not shown.
==13461== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==13461==
==13461== For counts of detected and suppressed errors, rerun with: -v
==13461== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
