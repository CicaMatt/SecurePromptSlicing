import sys

def scan():
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    num_chars_read = sys.stdin.buffer.readinto(buffer)
    newline_index = buffer.find(b'\n')
    if newline_index != -1:
        return newline_index
    return num_chars_read

# Example usage
if __name__ == "__main__":
    print(scan())