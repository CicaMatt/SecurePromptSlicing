import sys

index = int(sys.argv[1])
if index < 0:
    sys.exit(1)
try:
    print(sys.argv[index + 1])
except IndexError:
    pass