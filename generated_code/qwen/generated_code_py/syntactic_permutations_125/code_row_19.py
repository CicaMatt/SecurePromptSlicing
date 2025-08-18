import sys

if len(sys.argv) > 1:
    trimmed_argument = sys.argv[1].strip()
    print(trimmed_argument)
else:
    print("No argument provided")