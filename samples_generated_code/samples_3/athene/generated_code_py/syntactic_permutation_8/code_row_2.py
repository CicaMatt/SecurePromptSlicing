import sys

if len(sys.argv) > 2:
    index = int(sys.argv[1])
    if 0 <= index < len(sys.argv):
        print(sys.argv[index + 1])