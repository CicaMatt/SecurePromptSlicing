import sys

if len(sys.argv) != 2:
    print("Usage: please provide one filename as an argument")
    exit()

filename = sys.argv[1].rstrip()
print(filename)
exit()