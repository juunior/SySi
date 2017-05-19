#!/bin/bash

if [ $# == 0 ]; then
	echo "this operation needs at least one argument"
else
	for i ;do
		echo Hallo $i
	done
fi
