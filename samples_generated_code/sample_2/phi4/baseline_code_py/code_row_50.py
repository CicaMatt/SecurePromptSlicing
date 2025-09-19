import sys

if len(sys.argv) != 2:
    print("Usage: python3 script.py <buffer_size>")
    sys.exit(1)

try:
    buffer_size = int(sys.argv[1])
except ValueError:
    print("Buffer size must be an integer.")
    sys.exit(1)

# Allocate the buffer
buffer = bytearray(buffer_size)

# Fill the buffer with some data (for demonstration)
for i in range(buffer_size):
    buffer[i] = i % 256

# Print the contents of the buffer
print("Buffer contents:")
print(list(buffer))

# Exit the program
sys.exit(0)