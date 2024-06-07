#!/bin/bash

# Get amount of runs from command line, default to 3000
if [ $# -eq 0 ]
then
    runs=3000
else
    runs=$1
fi

make -C build clean
make -C build

for i in `seq 1 $runs`
do
    seed=$RANDOM
    ./bin/main -P 0-999 -o prof.log -b -S $seed
    ./bin/main -P 0-999 -o nozes.log -b -r 105-105 -S $seed
    # Diff, if different, print the seed and exit
    diff prof.log nozes.log > /dev/null
    if [ $? -ne 0 ]
    then
        echo "Seed: $seed"
        echo "Iteration: $i"
        meld "nozes.log" "prof.log"
        exit 0
    fi
done