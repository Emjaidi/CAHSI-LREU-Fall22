#! /bin/bash

date +%H:%M:%S >> results.txt
sum=0
for ((n=0;n<5;n++))
    do
        program=($(./main))
        echo "$program," >> results.txt
        sum=$(echo "scale=8;$sum+$program" | bc)
done

echo "scale=8; $sum/$n" | bc
