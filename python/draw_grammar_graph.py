#!/usr/bin/env python

import sys

'''
Usage: dwar_grammar_graph <grammar.jj> | dot
'''
def main():
    if 1 == len(sys.argv):
        return 1
    relations = {}
    cat = None
    with open(sys.argv[1]) as gf:
        for line in gf:
            print line,
            if ':' in line:
                print 'is def!',
                for token in line.split(' '):
                    if '()' in token:
                        cat = token[:len(token)-2]
                        print 'DEFINING:',cat
                        #relations[cat] = set()
                continue
            print

            for token in line.strip().replace('<', ' ').replace('>', ' ').replace('|', ' ').split(' '):
                print token,
                if len(token) > 1 and '(' in token and ')' in token:
                    print 'valid',
                    #relations[cat].add(token[:token.find('(')])
                    relations.setdefault(token[:token.find('(')], []).append(cat)
                print

    print 'digraph', sys.argv[1].split('/')[-1].split('.')[0], '{'
    for a in relations:
        if len(a) and ';' not in a and '}' not in a:
            for b in set(relations[a]):
                print b,'->',a,';'
    print '}'

if __name__ == '__main__':
    main()