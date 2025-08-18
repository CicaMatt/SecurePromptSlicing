import sys

def convert_to_int(s):
    return int(s)

if len(sys.argv) > 1:
    INDEX = convert_to_int(sys.argv[1])
    if len(sys.argv) > INDEX:
        print(sys.argv[INDEX])