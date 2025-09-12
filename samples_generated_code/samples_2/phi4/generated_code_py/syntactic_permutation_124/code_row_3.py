import sys

if len(sys.argv) != 2:
    print("Exactly one argument is required.")
    sys.exit(1)

arg = sys.argv[1].rstrip()
print(arg)
sys.exit(0)