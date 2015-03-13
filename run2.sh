#!/bin/bash

echo "Beginning I2C connection status check"
i2cdetect -y 1
echo ""
echo ""

echo "Lighting LED on Chip 1:"
./i2c1 1
read -rsp $'Press key to continue without 5 second pause...' -t5 -n1
echo "Continuing..."
echo ""

echo "Turning off LED on Chip 1:"
./i2c1 1
echo ""

echo "Turning on LED on chip 2:"
./i2c2 3
read -rsp '2 second pause or keypress to skip' -t5 -n1
if ["$?" == "0"]; then
	echo "pause skipped."
	echo ""
else
	echo ""
fi

echo "Turning off LED on Chip 2."
./i2c2 3
echo ""

echo "Turning LED on and off on chip 1 & 2:"
for i in {1..3}
do
	./i2c2 3
	sleep 1
	./i2c1 1
	sleep 1
	./i2c2 3
	sleep 1
	./i2c1 1
	sleep 1
done
echo ""

echo "Reading internal temp from chip 1:"
./i2c1 2
echo ""

echo "Reading internal temp from chip 2:"
./i2c2 4
echo ""

echo "Program completed."
