#!/bin/bash

echo -n "Enter number: ";
read num;

fact=1;

if [ $num -lt 0 ]; then
	echo "Must enter a positive number";
fi

while [ $num -gt 0 ]; do
	fact=$(($fact*$num));
	num=$(($num-1));
done

echo "Factorial: $fact";
