#!/bin/bash

# indexer parameters
crawlerdir=/net/class/cs50/demo/crawler-output/cs50/depth
output=output/
# ./indexer /net/class/cs50/demo/crawler-output/cs50/depth0 indexfile0
# ./indextest indexfile0 testresult0

sorted=.sorted

# remove output from previous run
for depth in 0 1 2 3
do
  rm -rf $output
  mkdir -p $output
done

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

# Depth 0 ----------------------------------

echo
echo indexer depth 0
./indexer ${crawlerdir}0 ${output}indexfile0

echo
echo indextest depth 0
./indextest ${output}indexfile0 ${output}testresult0

echo
echo sort and compare: indexfile0 testresult0
gawk -f indexsort.awk ${output}indexfile0 > ${output}indexfile0.sorted
gawk -f indexsort.awk ${output}testresult0 > ${output}testresult0.sorted
# compare files using diff -q switch: http://www.computerhope.com/unix/udiff.htm
diff -q ${output}indexfile0.sorted ${output}testresult0.sorted
if [ $? -eq 0 ]
  then
  printf "success! no differences\n"
else
  printf "failed: files are different\n"
fi

# Depth 1 ----------------------------------

echo
echo indexer depth 1
./indexer ${crawlerdir}1 ${output}indexfile1

echo
echo indextest depth 1
./indextest ${output}indexfile1 ${output}testresult1

echo
echo sort and compare: indexfile1 testresult1
gawk -f indexsort.awk ${output}indexfile1 > ${output}indexfile1.sorted
gawk -f indexsort.awk ${output}testresult1 > ${output}testresult1.sorted

diff -q ${output}indexfile1.sorted ${output}testresult1.sorted
if [ $? -eq 0 ]
  then
  printf "success! no differences\n"
else
  printf "failed: files are different\n"
fi

# Depth 2 ----------------------------------

echo
echo indexer depth 2
./indexer ${crawlerdir}2 ${output}indexfile2

echo
echo indextest depth 2
./indextest ${output}indexfile2 ${output}testresult2

echo
echo sort and compare: indexfile2 testresult2
gawk -f indexsort.awk ${output}indexfile2 > ${output}indexfile2.sorted
gawk -f indexsort.awk ${output}testresult2 > ${output}testresult2.sorted

diff -q ${output}indexfile2.sorted ${output}testresult2.sorted
if [ $? -eq 0 ]
  then
  printf "success! no differences\n"
else
  printf "failed: files are different\n"
fi

# Depth 3 ----------------------------------

echo
echo indexer depth 3
./indexer ${crawlerdir}3 ${output}indexfile3

echo
echo indextest depth 3
./indextest ${output}indexfile3 ${output}testresult3

echo
echo sort and compare: indexfile3 testresult3
gawk -f indexsort.awk ${output}indexfile3 > ${output}indexfile3.sorted
gawk -f indexsort.awk ${output}testresult3 > ${output}testresult3.sorted

diff -q ${output}indexfile3.sorted ${output}testresult3.sorted
if [ $? -eq 0 ]
  then
  printf "success! no differences\n"
else
  printf "failed: files are different\n"
fi

exit 0
