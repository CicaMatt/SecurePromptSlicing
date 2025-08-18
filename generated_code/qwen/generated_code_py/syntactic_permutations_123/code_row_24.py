import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]

if not isinstance(arg, str):
    raise TypeError("The argument must be a string")

arg = arg.rstrip()
arg = arg.replace('\n', '')
arg += '\0'

print(repr(arg))