#!/bin/bash

# iterate all .in files in /tests directory
for f in tests/*.in
do
	echo "Test nr $f: "
	fullname=$(basename S$f)
	filename=${fullname%.*} #file name without extension
	outFile=$filename".out"
	errFile=$filename".err"
	./szpital -v < $f > tmp.out 2> /dev/null
	result=$(diff tmp.out tests/$outFile)
	if [ $? -eq 0 ] 
	then
		echo "OK .out"
	else
		echo "ERROR .out"
	fi
	./szpital -v < $f 2> tmp.err > /dev/null
	result=$(diff tmp.err tests/$errFile)
	if [ $? -eq 0 ] 
	then
		echo "OK .err"
	else
		echo "ERROR .err"
	fi
	
done
