import sys

if len(sys.argv) > 1:
    argument = sys.argv[1].rstrip()
    print(argument)
else:
    print("No command line argument provided")