import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]

for i in range(len(arg)):
    arg = arg.rstrip()

for i in range(len(arg)):
    arg = arg.replace('\n', '')

arg += '\0'