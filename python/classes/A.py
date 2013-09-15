#!/usr/bin/env python

class A(object):
    def __init__(self):
        print 'init A'

    def method1(self):
        print 'method1 in A'

    def method2(self):
        print 'method2 in A'

class B (A):
    def __init__(self):
        #A.__init__(self)
        print 'init B'

    def method1(self):
        print 'method1 in B'


def main():
    print "Let's test this damn inheritance in Python"

    print 'Creating A'
    a = A()

    print 'Creating B'
    b = B()
    a.method1()
    b.method1()
    b.method2()


if __name__ == '__main__':
    main()
