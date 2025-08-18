import sys

if len(sys.argv) != 2:
    print("Error: Expected exactly one argument.")
    sys.exit(1)

argument = sys.argv[1].rstrip()
print(argument)
sys.exit(0)