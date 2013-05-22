#!/bin/bash

for x in $(ls $1); do
    if [ -d $x -a -d $x/.git ]; then
	git status | 
	echo "Pushing $x"
	cd $x
	git push
    fi
done