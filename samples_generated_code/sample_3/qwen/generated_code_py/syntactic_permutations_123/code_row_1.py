import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]

if not isinstance(arg, str):
    raise TypeError("Argument must be a string")

for _ in range(len(arg)):
    arg = arg.rstrip()

for _ in range(len(arg)):
    arg = arg.replace('\n', '')

arg += '\0'