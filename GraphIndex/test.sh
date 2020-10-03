#!/bin/bash
#$1 for hop length

echo "$1 for hop, $2 for labelsize"

rm CMakeCache.txt

cmake .

make

./main graph/slashdot$2 $1 $2

./main graph/dblp-un$2 $1 $2

./main graph/twitter$2 $1 $2
