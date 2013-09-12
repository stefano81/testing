#!/usr/bin/env python

import sys
import csv

def main():
    print 'create table country (id integer primary key, country_code text);'
    print 'create table ip (id integer, start integer, end integer);'
    print 'create table command (id integer, filename text, command text);'

    with open(sys.argv[1], r'r') as datafile:
        csv_reader = csv.reader(datafile)
        countries = {}
        for record in csv_reader:
            countries.setdefault(record[4], []).append((record[2], record[3]))

        i = 0
        for k in sorted(countries):
            print 'insert into country (id, country_code) values (' + str(i) + ', "' + k + '");'
            for (s, e) in countries[k]:
                print 'insert into ip (id, start, end) values (' + str(i) + ', ' + s + ', ' + e + ');'
            i = i + 1

if __name__ == '__main__':
    main()
