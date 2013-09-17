#!/usr/bin/env python

import sys
import fileinput

def main():
    if sys.argv[1:]:
        print 'using sys.stdin'
        for line in sys.stdin:
            print 'from input>',line.strip()
    else:
        print 'using fileinput'
        for line in fileinput.input():
            print 'from input>',line.strip()

if __name__ == '__main__':
    main()
