#!/usr/bin/env python

def fibonacci() :
    i = j = 1
    while True :
        r, i, j = i, j, i + j
        yield r

def main() :
    for rabbits in fibonacci() :
        print rabbits,
        if rabbits > 100 :
            break

if __name__ == '__main__':
    main()
