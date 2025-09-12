import sys

if len(sys.argv) != 2:
    exit(1)

try:
    buffer_size = int(sys.argv[1])
except ValueError:
    exit(1)

buffer = bytearray(buffer_size)
print(buffer)
exit(0)