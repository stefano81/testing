#!/usr/bin/env python

from time import time

def main() :
    vals = [x for x in range(1, 101)]

    h = []
    l = []
    for x in range(100):
        t0 = time()
        highlevel(*vals)
        t1 = time()
        h.append(t1 - t0)
        
        t0 = time()
        lowlevel(*vals)
        t1 = time()
        l.append(t1 - t0)
    
    print 'Highlevel', sum(*h)/100, max(h), min(h)
    print 'Lowlevel', sum(*l)/100, max(l), min(l)

def highlevel(*a) :
    return sum(x * x for x in a)

def lowlevel(*a) :
    total = 0
    for x in a:
        total += x * x
    return total

if __name__ == '__main__':
    main()
