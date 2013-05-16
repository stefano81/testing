#!/usr/bin/env python

import sys
import re

def main():
    regexp = r'^[0-9]{4}(-((0[1-9])|((1(0|1|2))))(-((0[1-9])|((1|2)[0-9])|((3(0|1))))([tT](((0|1)[0-9])|(2[0-3])):[0-5][0-9](:[0-5][0-9](\.[0-9]+)?)?([zZ]|([\+-](([0-1][0-9])|(2[0-3])):[0-5][0-9])))?)?)?$'
    prog = re.compile(regexp)
    line = sys.stdin.readline().strip()
    while 0 != len(line):
        if prog.match(line) is not None:
            print 'Correct:',line
        else:
            print 'Incorrect:',line
        line = sys.stdin.readline().strip()
        
if __name__ == '__main__':
    main()
