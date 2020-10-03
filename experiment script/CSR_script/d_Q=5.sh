#!/bin/bash

labelsize="64"

hopsize="3"

diameter="5"

queryNum="1"

pathlength="3"

pathNum="2"



##### QueryGenerator

cd QueryGenerator

#rm -rf Query-Slashdot/*

#rm -rf Query-DBLP/*

#rm -rf Query-Twitter/*

./test.sh $diameter $queryNum $labelsize

cd ../

#rm -rf query/Query-Slashdot/*

#rm -rf query/Query-DBLP/*

#rm -rf query/Query-Twitter/*


cp -rf QueryGenerator/Query-Slashdot/* PathGenerator/Query-Slashdot/

cp -rf QueryGenerator/Query-DBLP/* PathGenerator/Query-DBLP/

cp -rf QueryGenerator/Query-Twitter/* PathGenerator/Query-Twitter/

cp -rf QueryGenerator/Query-Slashdot/* query/Query-Slashdot/

cp -rf QueryGenerator/Query-DBLP/* query/Query-DBLP/

cp -rf QueryGenerator/Query-Twitter/* query/Query-Twitter/


##### PathGenerator

cd PathGenerator

./test.sh $pathlength $pathNum $queryNum $labelsize

cd ../

cp -rf PathGenerator/Path-Slashdot/* path/Path-Slashdot/

cp -rf PathGenerator/Path-DBLP/* path/Path-DBLP/

cp -rf PathGenerator/Path-Twitter/* path/Path-Twitter/


##### Test

#rm -rf results/*

rm CMakeCache.txt

cmake .

make

for((i=1;i<=$queryNum;i++));
do
./main query/Query-Slashdot/S$i-$labelsize graph/slashdot$labelsize path/Path-Slashdot/S$i-$labelsize index/S-Index1-$labelsize index/S-Index2-$labelsize $hopsize
done

for((i=1;i<=$queryNum;i++));
do
./main query/Query-DBLP/D$i-$labelsize graph/dblp-un$labelsize path/Path-DBLP/D$i-$labelsize index/D-Index1-$labelsize index/D-Index2-$labelsize $hopsize
done

for((i=1;i<=$queryNum;i++));
do
./main query/Query-Twitter/T$i-$labelsize graph/twitter$labelsize path/Path-Twitter/T$i-$labelsize index/T-Index1-$labelsize index/T-Index2-$labelsize $hopsize
done






