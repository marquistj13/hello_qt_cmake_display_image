#!/bin/bash
rm -rf build
DIR=`pwd`
mkdir build
cd build
cmake  ../
make -j4
#./bin/hdmap-main
cd $DIR
