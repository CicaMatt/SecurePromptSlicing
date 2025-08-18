import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    bytes_read = sys.stdin.buffer.readinto(buffer)
    if b'\n' in buffer:
        newline_index = buffer.index(b'\n')
        result = buffer[:newline_index].decode('utf-8')
        return len(result)
    else:
        return min(bytes_read, buffer_size - 1)

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))