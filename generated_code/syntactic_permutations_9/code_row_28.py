import sys

try:
    index = int(sys.argv[1])
except IndexError:
    print("No index specified!")

print(sys.argv[index])