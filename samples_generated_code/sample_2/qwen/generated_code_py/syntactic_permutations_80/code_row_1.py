import sys

def scan(buffer_size=1024):
    import io
    buf = bytearray(buffer_size)
    num_chars_read = sys.stdin.buffer.readinto(buf)
    newline_index = buf.find(b'\n')
    if newline_index != -1:
        return newline_index + 1
    else:
        return num_chars_read

# Example usage:
if __name__ == "__main__":
    result = scan()
    print(f"Number of characters read: {result}")