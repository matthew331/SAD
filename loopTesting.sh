#!/bin/bash
for i in {1..5}
do
	make run > ./result/run-$i.log
done
