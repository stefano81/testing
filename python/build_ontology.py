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


def get_type(jtype, package, imports):
    if jtype in imports:
        return imports[jtype]
    v = jtype.lower()
    if not ('byte' == v or 'double' == v or 'int' == v or 'boolean' == v or 'long' == v or 'string' == v):
        return '.'.join((package, jtype))
    return jtype

def extract_ontoclass(javafile):
    with open(javafile, 'r') as jfile:
        oc = False
        inClass = False
        nextPred = False
        package = None
        properties = []
        imports = {}

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
                    c = match.group(2)
            elif not inClass:
                match = e_pattern.match(line)
                if match:
                    inClass = True
                    if package:
                        jc = '.'.join((package,match.group(1)))
                    else:
                        jc = match.group(1)
            elif not nextPred:
                match = pc_pattern.match(line)
                if match:
                    p = match.group(1)
                    nextPred = True
            else:
                match = object_pattern.match(line)
                if match:
                    nextPred = False
                    properties.append( (p, get_type(match.group(6), package, imports)) )

    if oc:
        return (jc, c, properties)
    else:
        return (None, None, None)

def get_ontotype(orig_type, classes):
    if orig_type in classes:
        sys.stderr.write('{} is in classes as {}\n'.format(orig_type, classes[orig_type][0]))
        return classes[orig_type][0]

    sys.stderr.write('{} is not in classes\n'.format(orig_type))
    return orig_type

def build_classes(rootdir):
    classes = {}
    for dirpath, dirnames, filenames in os.walk(rootdir):
        for f in filenames:
            if f.endswith('.java'):
                jc, c, p = extract_ontoclass(os.path.join(dirpath, f))
                if jc and c and p:
                    sys.stderr.write('JavaClass: {}\n'.format(jc))
                    sys.stderr.write('OntoClass: {}\n'.format(c))
                    sys.stderr.write('Properties: {}\n'.format(p))

                    classes[jc] = (c, p)

    sys.stderr.write('########################################\n')
    sys.stderr.write('{}\n'.format(classes))
    sys.stderr.write('########################################\n')

    print "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>"
    print "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>"
    for k in sorted(classes):
        (c, p) = classes[k]
        print '<{}>'.format(c),'a rdfs:Class .'
        for pn, pt in p:
            print '<{}> a rdf:Property;'.format(pn)
            print '\t<{}> rdfs:range <{}>;'.format(pn, c)
            print '\t<{}> rdfs:domain <{}>.'.format(pn, get_ontotype(pt, classes))
        print

def main():
    if not sys.argv[1:]:
        print """
        Usage: build_ontology.py <start_directory>
        """
        return
    
    classes = build_classes(sys.argv[1:][0])

if __name__ == '__main__':
    main()
