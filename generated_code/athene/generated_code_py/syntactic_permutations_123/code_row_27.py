import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

for i in range(len(arg)):
    if arg[-i-1] != ' ':
        arg = arg[:-i] if i > 0 else arg
        break

for i in range(len(arg)):
    if arg[-i-1] != '\n':
        arg = arg[:-i] if i > 0 else arg
        break

arg = None