import sys

def str_to_int(s):
    return int(s)

if len(sys.argv) > 2:
    index = str_to_int(sys.argv[1])
    if 0 < index < len(sys.argv):
        print(sys.argv[index])