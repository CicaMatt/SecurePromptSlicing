import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

arg = arg.rstrip()
arg = arg.replace('\n', '')
arg = arg + '\0'