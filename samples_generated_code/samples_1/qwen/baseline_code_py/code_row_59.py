import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]
if not isinstance(arg, str):
    raise TypeError("Argument must be a string")

for _ in range(len(arg)):
    if arg.endswith(' '):
        arg = arg[:-1]

for _ in range(len(arg)):
    if arg.endswith('\n'):
        arg = arg[:-1]

arg += '\0'