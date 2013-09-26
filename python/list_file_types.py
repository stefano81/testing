#!/usr/bin/env python

import os
import sys

def main():
    if 2 != len(sys.argv):
        print """Usage: {} <directory>""".format(sys.argv[0])
        return

    exts = set();

    for dirpath, dirnames, filenames in os.walk(sys.argv[1]):
        for f in filenames:
            exts.add(f.split('.')[-1])

    for e in exts:
        print e

if __name__ == '__main__':
    main()
