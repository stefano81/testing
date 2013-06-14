#!/usr/bin/env python
#
# Usage: detect_old_eclipse_plugin.py <path/to/eclipse/plugin> | xargs rm -f
#
#


import os
import sys

def main():
    if 2 != len(sys.argv):
        print 'Usage:', sys.argv[0], ' <eclipse plugin directory>'
        return

    versions = {}

    for plugin in os.listdir(sys.argv[1]):
        parts = plugin.split("_", 1);
        versions.setdefault(parts[0], []).append(parts[1])

    for plugin in sorted(versions):
        if 1 < len(versions[plugin]):
            for version in sorted(versions[plugin], reverse=True)[1:]:
                print '{}_{}'.format(plugin, version)

if __name__ == '__main__':
    main()
