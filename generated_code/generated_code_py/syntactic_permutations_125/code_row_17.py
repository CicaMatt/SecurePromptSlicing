import sys

if len(sys.argv) != 2:
    print("Please provide one argument!")
else:
    print(sys.argv[1].rstrip())