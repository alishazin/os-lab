#!/bin/bash

echo -n "Enter first number: ";
read fnum;

echo -n "Enter second number: ";
read snum;

#sum=$(($fnum + $snum)); # no space before and after =, works without $
#sum=`expr $fnum + $snum`;
sum=$(expr $fnum + $snum);

echo "Sum: ${sum}";
