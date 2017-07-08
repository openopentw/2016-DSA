#!/bin/bash
chmod +x ./bin/verify ./bin/format 
make || exit 1
rm time_log
for i in $(seq 1 9)
do
    echo testing... data$i
	name="testdata/random_30x30_0$i.txt"
	out="testdata/output_0$i.txt"
        time ( make run -s <$name >$out) 2>>time_log
	echo diffing
	./bin/verify <$out >testdata/$i.in
	./bin/format <$name >tmp
	diff tmp "testdata/$i.in"
	echo finished
done
for i in $(seq 10 38)
do
    echo testing... data$i
	name="testdata/random_30x30_$i.txt"
	out="testdata/output_$i.txt"
        time ( make run -s <$name >$out) 2>>time_log
	echo diffing
	./bin/verify <$out >testdata/$i.in
	./bin/format <$name >tmp
	diff tmp "testdata/$i.in"
	echo finished
done
rm tmp testdata/*.in
rm testdata/output* 
