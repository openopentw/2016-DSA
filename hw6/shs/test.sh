#!/usr/bin/env bash
make
if ! [ -f check.out ] ;then
    wget -q https://www.csie.ntu.edu.tw/~b04902031/files/check.out
fi
chmod 0700 ./check.out
for (( i = 1; i < 49; i++ )); do
	N="${i}"
	if [[ $i -lt 10 ]]; then
		N="0${i}"
	fi
	echo "Test Case $N:"
	echo "" > log
	echo "" > ERR
	curl -s  "http://mirlab.org/jang/courses/dsa/homework/2016/hw06/testSet/${N}_input.txt" | ( time make run -s > out ) 2>>log
	diff -b out <(curl -s "http://mirlab.org/jang/courses/dsa/homework/2016/hw06/testSet/${N}_output.txt") > tmp
	c=$(cat tmp | wc -l | tr -d ' ')
	if [[ "${c}" == "0" ]]; then
		echo "0" >>ERR
		./check.out
	elif [[ "${c}" == "4" ]]; then
		echo "$(cat tmp | tail -n 1 | tr -d '>')-$(cat tmp | tail -n 3 | head -n 1 | tr -d '<')" | bc -q | tr -d '-' >>ERR
		./check.out
	else
		echo "Wrong Answer"
	fi
	# rm -f log ERR
done
rm -f tmp
rm -f check.out
rm -f out
