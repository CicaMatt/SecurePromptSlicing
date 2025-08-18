import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
else:
    argument = sys.argv[1].rstrip()
    print(argument)
    exit(0)