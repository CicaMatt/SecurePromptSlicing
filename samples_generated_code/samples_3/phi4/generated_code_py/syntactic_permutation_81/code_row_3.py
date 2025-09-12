import sys

def allocate_buffer():
    return bytearray(1024)

def read_to_buffer(buf):
    data = sys.stdin.read(10)
    for i, char in enumerate(data[:10]):
        buf[i] = ord(char)

# Example usage:
buf = allocate_buffer()
read_to_buffer(buf)
print(buf[:10])  # Output the first 10 bytes to verify