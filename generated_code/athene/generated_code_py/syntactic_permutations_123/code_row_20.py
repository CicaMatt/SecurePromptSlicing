import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

for char in arg:
    if char == ' ':
        arg = arg.replace(char, '')

for newline in ('\n', '\r'):
    arg = arg.replace(newline, '')

arg += '\0'