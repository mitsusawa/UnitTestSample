#!/bin/bash

cd ./build
rm -Rf ./CMakeCache.txt
cmake -G"Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
ninja
cd ../
