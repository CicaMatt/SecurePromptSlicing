import sys

def convert_string_to_int(s):
    return int(s)

if len(sys.argv) > 2:
    index = convert_string_to_int(sys.argv[1])
    if index < len(sys.argv):
        print(sys.argv[index])