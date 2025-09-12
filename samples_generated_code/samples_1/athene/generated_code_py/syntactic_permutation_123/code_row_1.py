import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

for i in range(len(arg) - 1, -1, -1):
    if arg[i] != ' ':
        arg = arg[:i+1]
        break

for i in range(len(arg) - 1, -1, -1):
    if arg[i] != '\n':
        arg = arg[:i+1]
        break

arg += '\0'