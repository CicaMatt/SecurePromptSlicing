import sys

if len(sys.argv) != 2:
    exit(1)

arg = sys.argv[1].rstrip()
arg = arg.replace('\n', '')

arg += '\0'