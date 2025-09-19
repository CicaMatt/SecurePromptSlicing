import sys

if len(sys.argv) > 1:
    argument = sys.argv[1]
    print(argument.rstrip())
else:
    print("No command line argument provided")