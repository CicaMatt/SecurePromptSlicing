import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <buffer_size>")
    sys.exit(1)

try:
    buffer_size = int(sys.argv[1])
except ValueError:
    print("Please provide a valid integer for buffer size.")
    sys.exit(1)

# Allocate the buffer
buffer = bytearray(buffer_size)

# Fill with arbitrary data (e.g., zeros) and print contents
print(f"Buffer of size {buffer_size} allocated:")
for i in range(buffer_size):
    buffer[i] = 0  # or some other value if desired

print(list(buffer))