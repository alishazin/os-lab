#!/bin/bash

ARR[0]="Ali";
ARR[1]=10;
ARR[3]="Shazin";

echo "0: ${ARR[0]}";

echo "All: ${ARR[*]}";
echo "All: ${ARR[@]}";

# for loop example

for i in 0 1 2; do
	#if [ $i -ge 2 ]; then
	#	break 1;
	#fi;
	echo "$i: ${ARR[$i]}";
done
