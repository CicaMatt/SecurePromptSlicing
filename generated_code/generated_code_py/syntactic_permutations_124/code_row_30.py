import sys

if len(sys.argv) != 2:
    print("Usage: please provide a name")
    sys.exit()

name = sys.argv[1]
print(name)

trimmed_name = name.rstrip()
print(trimmed_name)