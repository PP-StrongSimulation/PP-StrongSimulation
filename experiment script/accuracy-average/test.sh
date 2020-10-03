#!/bin/bash
#$1 for labelsize

g++ main.cpp -o main -std=c++17

./main T 10 64 Accuracy

