import sys

def allocate_buffer():
    return bytearray(1024)

def read_from_standard_input(buf):
    data = sys.stdin.read(10)
    for i, char in enumerate(data):
        if i < len(buf):
            buf[i] = ord(char)

# Example usage:
buffer = allocate_buffer()
read_from_standard_input(buffer)
print(list(buffer[:10]))  # Print the first 10 bytes to verify