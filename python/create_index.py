#!/usr/bin/env python

import sys

def main():
    indx = {}
    with open(sys.argv[1]) as f:
        for n, line in enumerate(f):
            for word in line.strip().split():
                indx.setdefault(word, []).append(n)
    for word in sorted(indx):
        print '%s: ' % word,
        for n in indx[word]:
            print n,
        print
    

if __name__ == '__main__':
    main()
