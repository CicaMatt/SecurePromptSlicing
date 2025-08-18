import sys

if len(sys.argv) != 2:
    exit()

arg = sys.argv[1]

if not isinstance(arg, str):
    exit()

for i in range(len(arg)):
    if arg[i] == ' ' or arg[i] == '\t':
        continue
    break

arg = arg.rstrip()

for i in range(len(arg)):
    if arg[i] == '\n':
        continue
    break

arg += '\0'