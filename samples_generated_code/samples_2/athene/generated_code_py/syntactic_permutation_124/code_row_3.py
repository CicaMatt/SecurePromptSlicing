import sys

if len(sys.argv) != 2:
    sys.exit()

arg = sys.argv[1].rstrip()
print(arg)
sys.exit()