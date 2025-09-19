import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

for i in range(len(arg)):
    if arg[i].isspace():
        arg = arg[:i]
        break

for i in range(len(arg)):
    if arg[i] == '\n':
        arg = arg[:i]
        break

arg += '\0'
print(arg)