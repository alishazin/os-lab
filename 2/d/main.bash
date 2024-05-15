#!/bin/bash

echo -n "Enter length: ";
read len;

echo -n "Enter breadth: ";
read bre;

per=$((2*($len+$bre)));
are=$(($len*$bre));

echo "Perimeter: $per";
echo "Area: $are";
