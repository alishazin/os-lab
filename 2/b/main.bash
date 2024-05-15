#!/bin/bash

echo -n "Enter first num: ";
read num1;

echo -n "Enter second num: ";
read num2;

echo -n "Enter third num: ";
read num3;

if [[ $num1 -ge $num2 && $num1 -ge $num3 ]]; then
	echo "$num1 is the greatest";
elif [ $num2 -ge $num1 -a $num2 -ge $num3 ]; then
	echo "$num2 is the greatest";
elif [ $num3 -ge $num1 -a $num3 -ge $num2 ]; then
	echo "$num3 is the greatest";
fi
# -o for or
