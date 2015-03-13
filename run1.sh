#!/bin/bash

echo "This is my first batch file test."
echo "I will list the files in this directory:"
ls -lah
echo ""

echo "This is just the beginning"
echo "Watch me execute a simple file"
./hello
echo ""

echo "I can tell you today's date:"
cal
echo ""

echo "Now I will show you how I can loop:"
n=1
for f in The quick red fox jumps over the lazy brown dog; do
	echo "   Word number $n is $f"
	let n+=1
done
echo ""

echo "That's all folks!"
