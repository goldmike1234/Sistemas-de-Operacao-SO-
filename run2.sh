#!/bin/bash

make -C build clean
make -C build
./bin/main -b -r $1-$2 -o "1.txt" -i examples/p1a.txt
./bin/main -b -o "2.txt" -i examples/p1a.txt
meld "1.txt" "2.txt"
