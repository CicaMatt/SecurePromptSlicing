import sys

if len(sys.argv) != 2:
    exit(1)

arg = sys.argv[1]

for i in range(len(arg)):
    if arg[i] not in (' ', '\t'):
        arg = arg[i:]
        break

for i in range(len(arg)-1, -1, -1):
    if arg[i] not in ('\n', '\r'):
        arg = arg[:i+1]
        break

arg += '\0'
print(arg)