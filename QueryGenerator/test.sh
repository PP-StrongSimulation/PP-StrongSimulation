#!/bin/bash
#$1 for diameter $2 for query number

echo "$1 for diameter, $2 for query number, $3 for labelsize"

rm CMakeCache.txt

cmake .

make

./main graph/slashdot$3 $1 $2 $3

./main graph/dblp-un$3 $1 $2 $3

./main graph/twitter$3 $1 $2 $3
