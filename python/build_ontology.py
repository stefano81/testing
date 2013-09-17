#!/usr/bin/env python

import os
import re
import sys

oc_pattern = re.compile('\s*@OntologyClass\((\s*value\s*=)?\s*"(.+)"\s*\)')
e_pattern = re.compile('\s*public\s*class\s*(.+)\s*extends\s*((AbstractSortableEntity<(.+)>)|Entity)')
pc_pattern = re.compile('\s*@PredicateClass\(\s*"(.+)"\s*\)')
package_pattern = re.compile('\s*package\s+(.+)\s*;')
object_pattern = re.compile('\s*((public)|(private)|(protected)\s*)?(.+)\s+(.+)\s+(.+)\s*;')
import_pattern = re.compile('\s*import\s*(.*)\s*;')

imports = {}


def get_type(type):
    if 'double' == type or 'int' == type or 'boolean' == type

def print_if_entity(javafile):
    with open(javafile, 'r') as jfile:
        oc = False
        inClass = False
        nextPred = False
        del package
        
        for line in jfile:
            if not line.strip():
                continue

            if not oc:
                match = import_pattern.match(line)
                if match:
                    class_name = match.group(1).split('.')[-1]
                    imports[class_name] = match.group(1)
                    continue

                match = package_pattern.match(line)
                if match:
                    package = match.group(1)
                    continue

                match = oc_pattern.match(line)
                if match:
                    oc = True
                    print 'OC',match.group(2),
            elif not inClass:
                match = e_pattern.match(line)
                if match:
                    inClass = True
                    try:
                        if package:
                            print '.'.join((package,match.group(1)))
                    except NameError:
                        print match.group(1)
            elif inClass and not nextPred:
                match = pc_pattern.match(line)
                if match:
                    print 'PC',match.group(1),
                    nextPred = True
            elif inClass and nextPred:
                match = object_pattern.match(line)
                if match:
                    nextPred = False
                    print get_type(match.group(6))
            else:
                print 'something went wrong"',line,'"'

def main():
    if not sys.argv[1:]:
        print """
        Usage: build_ontology.py <start_directory>
        """
        return
    
    for dirpath, dirnames, filenames in os.walk(sys.argv[1:][0]):
        for f in filenames:
            if f.endswith('.java'):
                print_if_entity(os.path.join(dirpath, f))

if __name__ == '__main__':
    main()
