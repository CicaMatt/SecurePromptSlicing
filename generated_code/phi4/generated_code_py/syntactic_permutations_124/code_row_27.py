import sys

if len(sys.argv) != 2:
    print("Error: Exactly one argument is required.")
    sys.exit(1)

argument = sys.argv[1]
trimmed_argument = argument.rstrip()
print(trimmed_argument)
sys.exit(0)