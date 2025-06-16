import sys

if len(sys.argv) == 2 :
    print(sys.argv[1].rstrip())
else :
    print("Please provide a command line argument")