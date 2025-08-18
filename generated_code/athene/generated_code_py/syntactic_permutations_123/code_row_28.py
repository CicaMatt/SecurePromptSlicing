import sys

if len(sys.argv) != 2:
    exit(1)

arg = sys.argv[1]
if not isinstance(arg, str):
    exit(1)

for char in arg[::-1]:
    if char.isspace():
        arg = arg[:-1]
    else:
        break

for char in arg[::-1]:
    if char == '\n':
        arg = arg[:-1]
    else:
        break

arg += '\0'
print(arg)