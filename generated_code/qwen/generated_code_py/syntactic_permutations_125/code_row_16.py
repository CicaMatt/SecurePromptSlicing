import sys

if len(sys.argv) > 1:
    trimmed_argument = sys.argv[1].rstrip()
    print(trimmed_argument)
else:
    print("No argument provided")