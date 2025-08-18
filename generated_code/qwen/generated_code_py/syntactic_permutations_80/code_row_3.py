import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    read_count = 0
    
    if format_string == "%s\n":
        while True:
            char = sys.stdin.buffer.read(1)
            if not char or char == b'\n':
                break
            if read_count < buffer_size - 1:  # Reserve one byte for the null terminator
                buffer[read_count] = char[0]
                read_count += 1
    
    return read_count

# Example usage:
if __name__ == "__main__":
    print(scan("%s\n"))