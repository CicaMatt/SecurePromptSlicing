import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]
arg = arg.rstrip()
for i in range(len(arg)):
    if arg[i] == '\n':
        arg = arg[:i] + arg[i+1:]
arg += '\0'
print(arg)