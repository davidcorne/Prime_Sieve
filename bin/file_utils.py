#!/usr/bin/env python
# Written by: DGC

import struct
try:
    import readline
    readline_imported = True
except ImportError:
    print("No tab completion.")
    readline_imported = False

import glob

#==============================================================================
def binary_file_to_list(file_name):
    uint_struct = struct.Struct("I")
    size = uint_struct.size
    return_list = []
    with open(file_name, "rb") as prime_file:
        while(True):
            if (prime_file.read(1) == ""):
                break
            # says move -1 relative to the current position
            prime_file.seek(-1, 1)
            return_list.append(uint_struct.unpack(prime_file.read(size))[0])
    return return_list

#==============================================================================
def ascii_file_to_list(file_name):
    return_list = []
    lines = None
    with open(file_name, "r") as prime_file:
        lines = prime_file.readlines()
    for prime in lines:
        return_list.append(int(prime))
    return return_list

#==============================================================================
def list_to_binary_file(primes, file_name):
    uint_struct = struct.Struct("I")
    size = uint_struct.size
    with open(file_name, "wb") as prime_file:
        for prime in primes:
            prime_file.write(uint_struct.pack(int(prime)))

#==============================================================================
def setup():
    if not readline_imported:
        return
    readline.set_completer_delims(' \t\n;')
    readline.parse_and_bind("tab: complete")
    readline.set_completer(__complete)

#==============================================================================
def __complete(text, state):
    return (glob.glob(text+'*')+[None])[state]

#==============================================================================
if (__name__ == "__main__"):
    setup()
    file_name = input("Binary file? ")
    for prime in binary_file_to_list(file_name):
        print(prime)
