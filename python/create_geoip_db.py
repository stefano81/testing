##!/usr/bin/env python

import sys
import csv

def main():
    print 'create table country (id integer primary key, country_code text);'
    print 'create table ip (start integer, end integer, country integer);'
    print 'create table command (id integer, command text);'

    with open(sys.argv[1], r'r') as datafile:
        csv_reader = csv.reader(datafile)
        countries = {}
        for record in csv_reader:
            countries.setdefault(record[4], []).append((int(record[2]), int(record[3])))

        i = 0
        for k in sorted(countries):
            print 'insert into country values ('+str(i)+', "'+k'");'
            #for (s, e) in countries[k]:

if __name__ == '__main__':
    main()
