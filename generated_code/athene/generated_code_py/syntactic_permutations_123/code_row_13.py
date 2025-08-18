import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

for i in range(len(arg)):
    if arg[-i-1] == ' ':
        arg = arg[:-i-1]
    else:
        break

for i in range(len(arg)):
    if arg[-i-1] == '\n':
        arg = arg[:-i-1]
    else:
        break

arg += '\0'
print(arg)