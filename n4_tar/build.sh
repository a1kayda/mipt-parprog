#!/bin/bash

gcc -fopenmp main.c -o task4

if [[ $? -eq 0 ]]
then
	echo Built, dou you want to run it\(y/n\)?
	read ans

	if [[ $ans == y ]]
	then
		./run.sh
	fi
else
	echo Oh no, it\'s not built
fi

