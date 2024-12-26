# run using "./check.sh test brute" 
#!/bin/bash
g++ gen.cpp -o gen
g++ -std=c++17 $1.cpp -o $1
g++ $2.cpp -o $2
for (( c=1; c <= 1000; c++ ))
do
    echo $c
    ./gen > inp
    ./$1 < inp > out1
    ./$2 < inp > out2
    diff -w out1 out2 > diff.txt
    if [ $? -ne 0 ]
    then
        echo "|     Input     |"
        cat inp
        echo ""
        echo "|    Output     |"
        cat out1
        echo ""
        echo "|    Accepted   |"
        cat out2
        echo ""
    fi
done