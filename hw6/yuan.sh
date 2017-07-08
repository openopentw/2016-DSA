#!/usr/bin/env bash
make
touch time_log_tmp
touch time_log
touch err_log_tmp
touch err_log
for (( i = 1; i < 49; i++ )); do
	N="${i}"
	if [[ $i -lt 10 ]]; then
		N="0${i}"
	fi
	( time make run < input/${N}.in > output/${N}.out) 2>> time_log_tmp
	diff output/${N}.out sample.output/${N}.out >> err_log_tmp
done
grep user time_log_tmp > time_log
grep -v "-" err_log_tmp > err_log
rm -f time_log_tmp
rm -f err_log_tmp
