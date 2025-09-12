import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

for i in range(len(arg)):
    if arg[i] not in ' \t':
        break
arg = arg[i:]

for i in range(len(arg)-1, -1, -1):
    if arg[i] not in '\n':
        break
arg = arg[:i+1]

arg += '\0'
print(arg)