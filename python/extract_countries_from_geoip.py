#!/usr/bin/env python

import sys
import csv

def main():
    with open(sys.argv[1], r'r') as datafile:
        csv_reader = csv.reader(datafile)
        countries = {}
        for record in csv_reader:
            if record[5] not in countries:
                countries[record[5]] = record[4]

        for k in sorted(countries):
            print '<option="' + countries[k] + '">' + k + '</option>'


if __name__ == '__main__':
    main()
