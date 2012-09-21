#!/usr/bin/env python
# Written by: DGC

# Parses a file made by running prime_finder.exe -c repeatedly
# Takes a file in the form:
# 10000
# Naive - run time: 0 seconds
# Sieve - run time: 0 seconds

# and turns it into a line 10000 0 0

# the file name can be piped into it.

import re

#==============================================================================
if (__name__ == "__main__"):
    lines = []
    file_name = raw_input("File name? ")
    with open(file_name, "r") as f:
        lines = f.readlines()
    assert len(lines) % 3 == 0
    print "Primes", "Naive", "Sieve"
    for l in lines:
        l = l.strip()
    for i in range(0, len(lines), 3):
        # the limit of primes
        print(int(lines[i])),
        
        naive = lines[i + 1]
        naive = re.sub("^.*: ", "", naive)
        naive = re.sub(" .*$", "", naive)
        print(float(naive)),

        sieve = lines[i + 2]
        sieve = re.sub("^.*: ", "", sieve)
        sieve = re.sub(" .*$", "", sieve)
        print(float(sieve))


