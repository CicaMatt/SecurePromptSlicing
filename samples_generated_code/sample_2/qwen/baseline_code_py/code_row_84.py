import sys

if len(sys.argv) > 1:
    print(sys.argv[1].rstrip())
else:
    print("No argument provided")