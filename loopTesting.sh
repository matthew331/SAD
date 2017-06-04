#!/bin/bash
for i in {1..50}
do
	echo "Run $i Start"
	make run > ./result/run-$i.log
	echo "Run $i Done"
done
