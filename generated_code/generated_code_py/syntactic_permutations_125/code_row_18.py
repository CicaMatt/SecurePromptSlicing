import sys
from string import whitespace

if __name__ == "__main__":
    arg = sys.argv[1]
    print(arg.rstrip(whitespace))