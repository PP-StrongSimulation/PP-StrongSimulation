#!/bin/bash
#$1 for labelsize

echo "$1 for label size"

g++ main.cpp -o main -std=c++17

./main graph/slashdot.txt $1

./main graph/dblp-un.txt $1

./main graph/twitter.txt $1
