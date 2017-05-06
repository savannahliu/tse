#!/bin/bash

# indexer parameters
crawlerdir=/net/class/cs50/demo/crawler-output/cs50/depth

# ./indexer /net/class/cs50/demo/crawler-output/cs50/depth0 indexfile0
# ./indextest indexfile0 testresult0

# indexer parameter tests ----------

echo
echo isnt a directory
./indexer TESTING.md indexfile
# usage: ./indexer pageDirectory must be a crawler produced directory

echo
echo isnt a crawler directory
./indexer pwd indexfile
# usage: ./indexer pageDirectory must be a crawler produced directory

echo
echo not readable directory
mkdir notreadable
chmod -r notreadable
./indexer notreadable indexfile
rm -rf notreadable
# usage: ./indexer pageDirectory must be a crawler produced directory

# ----------------------------------

echo
echo indexer depth 0
./indexer ${crawlerdir}0 indexfile0

echo
echo indextest depth 0
./indextest indexfile0 testresult0

echo
echo sort and compare: indexfile0 testresult0
gawk -f indexsort.awk indexfile0 > indexfile0.sorted
gawk -f indexsort.awk testresult0 > testresult0.sorted
# compare files using diff -q switch: http://www.computerhope.com/unix/udiff.htm
diff -q indexfile0.sorted testresult0.sorted
if [ $? -eq 0 ]
  then
  printf "success! no differences\n"
else
  printf "failed: files are different\n"
fi

exit 0
