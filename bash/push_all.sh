#!/bin/bash

for x in $(ls $1); do
    if [ -d $x -a -d $x/.git ]; then
	cd $x
	if [ $(git status | grep -q 'Your branch is ahead') ]; then
	    echo "Pushing $x"
	    #git push > /dev/null 2>&1
	else
	    echo "$x is updated"
	fi
	cd -
    fi
done