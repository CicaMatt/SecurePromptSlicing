import sys

def add_thousand(value):
    value = value + 1000
    print(value)
    return 0

add_thousand(int(sys.argv[1]))