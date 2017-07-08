#!/usr/bin/env bash
for (( i = 1; i < 49; i++ )); do
	N="${i}"
	if [[ $i -lt 10 ]]; then
		N="0${i}"
	fi
	echo "Test Case $N:"
	curl -s  "http://mirlab.org/jang/courses/dsa/homework/2016/hw06/testSet/${N}_input.txt" | make run -s > out
	diff -b out <(curl -s "http://mirlab.org/jang/courses/dsa/homework/2016/hw06/testSet/${N}_output.txt") > tmp
	c=$(cat tmp | wc -l | tr -d ' ')
	if [[ "${c}" == "0" ]]; then
		echo "No Error"
	elif [[ "${c}" == "4" ]]; then
		echo "$(cat tmp | tail -n 1 | tr -d '>')-$(cat tmp | tail -n 3 | head -n 1 | tr -d '<')" | bc -q | tr -d '-'
	else
		echo "Wrong Answer"
	fi
done
rm -f tmp
rm -f out
