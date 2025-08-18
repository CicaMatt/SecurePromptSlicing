import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit(1)

argument = sys.argv[1]
argument = argument.rstrip()
print(argument)
sys.exit(0)