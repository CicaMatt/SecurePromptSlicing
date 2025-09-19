import sys

def allocate_buffer():
    return bytearray(1024)

def read_input_into_buf(buf):
    input_data = sys.stdin.read(10)
    for i, char in enumerate(input_data):
        if i < len(buf):
            buf[i] = ord(char)

# Allocate a buffer of 1024 bytes
buffer = allocate_buffer()

# Read 10 characters from standard input and store them in the buffer
read_input_into_buf(buffer)

# For demonstration purposes, print out the first 10 values as characters
print("".join(chr(b) for b in buffer[:10]))