import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <buffer_size>")
    sys.exit(1)

try:
    buffer_size = int(sys.argv[1])
except ValueError:
    print("Buffer size must be an integer")
    sys.exit(1)

buffer = bytearray(buffer_size)
for i in range(buffer_size):
    buffer[i] = 0

print(buffer)