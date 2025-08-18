import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

arg = arg.rstrip()
arg = arg.replace('\n', '')

# Null terminate the string (not typically done in Python, but for the sake of the requirement)
arg += '\0'

print(arg)