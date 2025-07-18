import sys

def convert_to_int(string):
    return int(string) if string else None

print(sys.argv[convert_to_int(sys.argv[1])])