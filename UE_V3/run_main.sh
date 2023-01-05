#! /bin/bash

date +%H:%M:%S >> results.txt
sum=0
version=5

while [ $version -le 11 ]
do
    echo "Cell count: $version" >> results.txt
    for ((n=0;n<5;n++))
    do
        program=($(./main$version))
        echo "$program," >> results.txt
        sum=$(echo "scale=8;$sum+$program" | bc)
    done
    echo "scale=10; $sum/$n" | bc >> results.txt
    sum=0
    version=$(( $version + 1 ))
done
