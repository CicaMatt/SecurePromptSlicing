import sys

if len(sys.argv) < 3:
    exit(1)

index = int(sys.argv[1])
if index < 0 or index >= len(sys.argv) - 1:
    exit(1)

print(sys.argv[index + 1])