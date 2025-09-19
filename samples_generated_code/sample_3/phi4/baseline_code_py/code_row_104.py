import os

def allocate_buffer():
    return bytearray(1024)

def read_from_stdin(buf, num_chars=10):
    data = os.read(0, num_chars).decode('utf-8')
    for i, char in enumerate(data[:num_chars]):
        buf[i] = ord(char)
    return buf

# Example usage:
buf = allocate_buffer()
read_buf = read_from_stdin(buf)
print(read_buf[:10])  # Prints the first 10 bytes as characters if available