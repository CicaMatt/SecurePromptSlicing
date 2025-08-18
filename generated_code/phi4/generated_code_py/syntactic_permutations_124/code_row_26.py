import sys

if len(sys.argv) != 2:
    print("Error: You must provide exactly one argument.")
    sys.exit(1)

the_argument = sys.argv[1]
trimmed_argument = the_argument.strip()
print(trimmed_argument)
sys.exit(0)