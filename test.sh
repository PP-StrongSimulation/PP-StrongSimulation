#!/bin/bash

labelsize="64"

hopsize="4"

diameter="3"

queryNum="10"

pathlength="3"

pathNum="1"


##### Test

#rm -rf results/*

rm CMakeCache.txt

cmake .

make

for((i=1;i<=$queryNum;i++));
do
./main query/Query-Slashdot/S$i-$labelsize graph/slashdot$labelsize path/Path-Slashdot/S$i-$labelsize index/S-Index1-$labelsize index/S-Index2-$labelsize $hopsize $pathlength
done

for((i=11;i<=$queryNum;i++));
do
./main query/Query-DBLP/D$i-$labelsize graph/dblp-un$labelsize path/Path-DBLP/D$i-$labelsize index/D-Index1-$labelsize index/D-Index2-$labelsize $hopsize $pathlength
done

for((i=1;i<=$queryNum;i++));
do
./main query/Query-Twitter/T$i-$labelsize graph/twitter$labelsize path/Path-Twitter/T$i-$labelsize index/T-Index1-$labelsize index/T-Index2-$labelsize $hopsize $pathlength
done






