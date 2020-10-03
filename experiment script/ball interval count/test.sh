#!/bin/bash
#$1 for labelsize

g++ main.cpp -o main -std=c++17

./main S3-64-runtime 2000 8 3 5

