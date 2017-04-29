# CS50 Tiny Search Engine (TSE) Crawler Testing Documentation

Savannah Liu, April 2017.

## Test the program with various forms of command-line arguments
Directory name with many slashes. Works normally.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler/crawler-output]$ mkdir slashes/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/index.html crawler-output/slashes///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 0
 0   Fetched: http://old-www.cs.dartmouth.edu/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/index.html
```

Wrong number of parameters
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler
usage: ./crawler seedURL pageDirectory maxDepth
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/index.html crawler-output/test
usage: ./crawler seedURL pageDirectory maxDepth
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/index.html crawler-output/test 2 4 5
usage: ./crawler seedURL pageDirectory maxDepth
```

Test the crawler with a seedURL that points to a non-existent server.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$  ./crawler https://www.savannah.cs.buzzfeed.com/ crawler-output/test 1
usage: ./crawler seedURL must be internal
```

seedURL that points to a non-internal server.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler https://www.buzzfeed.com/ crawler-output/test 1
usage: ./crawler seedURL must be internal
```

seedURL that points to a valid server but non-existent page.
Outputs nothing. Nothing written to file.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/pineapples.html crawler-output/test 1
[sav@moose ~/cs50/labs/lab4/tse/crawler]$
```

## Test closed set of cross-linked pages, explore at depths 0, 1, 2, 3, 4, 5.
## Printed in log format (with logr) and checked directory to see if output is correct.
Depth 0. 1 file saved.  
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/letters/depth0/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth0/ 0

 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
```

Depth 1. 2 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/letters/depth1/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth1/ 1

 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
```

Depth 2. 3 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/letters/depth2/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth2/ 2
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 ```

Depth 3. 6 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/letters/depth3/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth3/ 3
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: https://en.wikipedia.org/wiki/Breadth-first_search
 3     IgnExtrn: https://en.wikipedia.org/wiki/Breadth-first_search
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 ```

Depth 4. 8 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/letters/depth4/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth4/ 4
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: https://en.wikipedia.org/wiki/Breadth-first_search
 3     IgnExtrn: https://en.wikipedia.org/wiki/Breadth-first_search
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 4         Found: https://en.wikipedia.org/wiki/ENIAC
 4      IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4         Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4         Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4         Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4       Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4         Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: https://en.wikipedia.org/wiki/Depth-first_search
 4      IgnExtrn: https://en.wikipedia.org/wiki/Depth-first_search
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 4         Found: https://en.wikipedia.org/wiki/Computational_biology
 4      IgnExtrn: https://en.wikipedia.org/wiki/Computational_biology
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
```

Depth 5. 9 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/letters/depth5/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./crawler-output/letters/depth5/ 5
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: https://en.wikipedia.org/wiki/Breadth-first_search
 3     IgnExtrn: https://en.wikipedia.org/wiki/Breadth-first_search
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 4         Found: https://en.wikipedia.org/wiki/ENIAC
 4      IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4         Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4         Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4         Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 4      Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 5          Found: https://en.wikipedia.org/wiki/Graph_traversal
 5       IgnExtrn: https://en.wikipedia.org/wiki/Graph_traversal
 5          Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 5          Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 5          Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 5        IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 5        Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 5          Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 4       Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4         Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 4      Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 5          Found: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 5       IgnExtrn: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 5          Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 5        IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 5          Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 5        IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: https://en.wikipedia.org/wiki/Depth-first_search
 4      IgnExtrn: https://en.wikipedia.org/wiki/Depth-first_search
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 4         Found: https://en.wikipedia.org/wiki/Computational_biology
 4      IgnExtrn: https://en.wikipedia.org/wiki/Computational_biology
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
```


## Test closed set of cross-linked pages but with different seedURL. Explore at depths 0, 1, 2, 3, 4, 5.
## Printed in log format (with logr) and checked directory to see if output is correct.

Test at depth 0. There is 1 file saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/lettersE/depth0/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./crawler-output/lettersE/depth0/ 0
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
```

Test at depth 1. There are 5 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/lettersE/depth1/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./crawler-output/lettersE/depth1/ 1
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 1      Found: https://en.wikipedia.org/wiki/ENIAC
 1   IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
```


Test at depth 2. There are 7 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/lettersE/depth2/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./crawler-output/lettersE/depth2/ 2
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 1      Found: https://en.wikipedia.org/wiki/ENIAC
 1   IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 2       Found: https://en.wikipedia.org/wiki/Graph_traversal
 2    IgnExtrn: https://en.wikipedia.org/wiki/Graph_traversal
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 2       Found: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2    IgnExtrn: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
```

Test at depth 3. There are 9 files saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/lettersE/depth3/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./crawler-output/lettersE/depth3/ 3
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 1      Found: https://en.wikipedia.org/wiki/ENIAC
 1   IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: https://en.wikipedia.org/wiki/Breadth-first_search
 3     IgnExtrn: https://en.wikipedia.org/wiki/Breadth-first_search
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 2       Found: https://en.wikipedia.org/wiki/Graph_traversal
 2    IgnExtrn: https://en.wikipedia.org/wiki/Graph_traversal
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 3        Found: https://en.wikipedia.org/wiki/Huffman_coding
 3     IgnExtrn: https://en.wikipedia.org/wiki/Huffman_coding
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 2       Found: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2    IgnExtrn: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 ```

 Test at depth 4. There are still only 9 files saved. It explores depth 4
 but doesn't save any depth 4 URLs because the closed-set of linked web pages
 is so small that it just keeps encountering external and duplicate URLs after depth 3.
```
 [sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/lettersE/depth4/
 [sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./crawler-output/lettersE/depth4/ 4
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 1      Found: https://en.wikipedia.org/wiki/ENIAC
 1   IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: https://en.wikipedia.org/wiki/Breadth-first_search
 3     IgnExtrn: https://en.wikipedia.org/wiki/Breadth-first_search
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: https://en.wikipedia.org/wiki/Depth-first_search
 4      IgnExtrn: https://en.wikipedia.org/wiki/Depth-first_search
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 4         Found: https://en.wikipedia.org/wiki/Computational_biology
 4      IgnExtrn: https://en.wikipedia.org/wiki/Computational_biology
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 2       Found: https://en.wikipedia.org/wiki/Graph_traversal
 2    IgnExtrn: https://en.wikipedia.org/wiki/Graph_traversal
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 3        Found: https://en.wikipedia.org/wiki/Huffman_coding
 3     IgnExtrn: https://en.wikipedia.org/wiki/Huffman_coding
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 2       Found: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2    IgnExtrn: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
```

Test at depth 5. There are still only 9 files saved. It never reaches a URL at depth 5
because the closed-set of linked web pages is so small that it just keeps encountering
external and duplicate URLs after depth 3.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/lettersE/depth5/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./crawler-output/lettersE/depth5/ 5

 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 1      Found: https://en.wikipedia.org/wiki/ENIAC
 1   IgnExtrn: https://en.wikipedia.org/wiki/ENIAC
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
 2       Found: https://en.wikipedia.org/wiki/Algorithm
 2    IgnExtrn: https://en.wikipedia.org/wiki/Algorithm
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: https://en.wikipedia.org/wiki/Breadth-first_search
 3     IgnExtrn: https://en.wikipedia.org/wiki/Breadth-first_search
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: https://en.wikipedia.org/wiki/Depth-first_search
 4      IgnExtrn: https://en.wikipedia.org/wiki/Depth-first_search
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3        Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 3     Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
 4         Found: https://en.wikipedia.org/wiki/Computational_biology
 4      IgnExtrn: https://en.wikipedia.org/wiki/Computational_biology
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
 4         Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 4       IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/G.html
 2       Found: https://en.wikipedia.org/wiki/Graph_traversal
 2    IgnExtrn: https://en.wikipedia.org/wiki/Graph_traversal
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2    Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 3        Found: https://en.wikipedia.org/wiki/Huffman_coding
 3     IgnExtrn: https://en.wikipedia.org/wiki/Huffman_coding
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
 3        Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 3      IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/F.html
 2       Found: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2    IgnExtrn: https://en.wikipedia.org/wiki/Fast_Fourier_transform
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/H.html
 2       Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
 2     IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
```

## Point the crawler at our Wikipedia playground. Explore at depths 0, 1, 2.
Depth 0. 1 file saved.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/wikipedia/depth0/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ crawler-output/wikipedia/depth0/ 0
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
```
mkdir crawler-output/wikipedia/depth0/
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ crawler-output/wikipedia/depth0/ 0


Depth 1. Saved 7 files.
```
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ mkdir crawler-output/wikipedia/depth1/
[sav@moose ~/cs50/labs/lab4/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ crawler-output/wikipedia/depth1/ 1
 0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
 0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
 0  Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
 1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
 1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
 1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
 1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
```

Depth 2
Output log is very long. Please see file crawler-output/wikipedia/depth2.log







exit 0
