import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

for i in range(len(arg)):
    if arg[i] == ' ' or arg[i] == '\n':
        arg = arg[:i]
        break

arg += '\0'