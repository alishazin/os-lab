#!/bin/bash

echo -n "Enter number to check: ";
read num;

if [[ $num -eq 0 || $num -eq 1 ]]; then
	echo "Not a prime number";
	exit 1;
fi

i=2;
flag=0;

while [ $i -le $(($num/2)) ]; do
	if [ $(($num%$i)) -eq 0 ]; then
		flag=1;
		break;
	fi
	i=$(($i+1));
done

if [ $flag -eq 0 ]; then
	echo "Prime number";
else
	echo "Not prime number";
fi
