#!/bin/bash

# iterate all .in files in /tests directory
if [ "$1" == "-v" ]
then
	prog=$2
	directory=$3
else
	prog=$1
	directory=$2
fi
for f in $directory/*.in
do
	echo "Test nr $f: "
	fullname=$(basename S$f)
	filename=${fullname%.*} #file name without extension
	outFile=$filename".out"
	errFile=$filename".err"
	./hospital -v < $f > tmp.out 2> tmp.err
	result=$(diff tmp.out tests/$outFile)
	if [ $? -eq 0 ] 
	then
		echo "OK .out"
	else
		echo "ERROR .out"
	fi
	if [ "$1" == "-v" ]
	then
		result=$(diff tmp.err tests/$errFile)
		if [ $? -eq 0 ]
		then
			echo "OK .err"
		else
			echo "ERROR .err"
		fi
	fi
	rm tmp.out tmp.err
done
