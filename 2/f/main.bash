#!/bin/bash

echo -n "Enter number of terms: ";
read num;

t1=0;
t2=1;
next=$(($t1+$t2));

if [ $num -gt 0 ]; then
	echo -n "$t1 ";
fi
if [ $num -gt 1 ]; then
	echo -n "$t2 ";
fi

i=3;

while [ $i -le $num ]; do
	echo -n "$next ";
	t1=$t2;
	t2=$next;
	next=$(($t1+$t2));
	i=$(($i+1));
done

echo "";
	
