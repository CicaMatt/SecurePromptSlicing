import sys

if len(sys.argv) != 2:
    sys.exit(1)

trimmed_argument = sys.argv[1].rstrip()
print(trimmed_argument)
sys.exit(0)