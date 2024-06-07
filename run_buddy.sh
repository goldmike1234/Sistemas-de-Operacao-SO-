#!/bin/bash

make -C build clean
make -C build
./bin/main -m 8 -k 4 -b -r $1-$2 -f buddy -o "eu.txt" -i examples/testes.txt
./bin/main -m 8 -k 4 -b -f buddy -o "prof.txt" -i examples/testes.txt
meld "eu.txt" "prof.txt"
