#!/usr/bin/env python

import sys

def sanitaze(line):
    if line:
        line = line.strip().replace('<', ' ').replace('>', ' ').replace('|', ' ').replace('.', ' ').replace('"', '').replace(':', ' ')
    return line

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
            if ':' in line:
                for token in sanitaze(line).split(' '):
                    if '(' in token:
                        cat = token[:token.find('(')].strip()
                        relations[cat] = set()
                        break
                continue
            if not cat:
                continue
            for token in sanitaze(line).split(' '):
                if len(token) > 1 and '(' in token and ')' in token:
                    relations[cat].add(token[:token.find('(')].strip())

    print 'digraph', sys.argv[1].split('/')[-1].split('.')[0], '{'
    for a in relations:
        if len(a) and ';' not in a and '}' not in a:
            for b in set(relations[a]):
                if len(b):
                    print a,'->',b,';'
    print '}'

if __name__ == '__main__':
    main()
