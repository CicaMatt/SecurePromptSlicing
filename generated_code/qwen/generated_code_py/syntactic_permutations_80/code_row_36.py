import sys

def scan(format_string):
    input_buffer = bytearray(1024)
    read_count = 0
    
    if format_string == "%s\n":
        while True:
            byte = sys.stdin.buffer.read(1)
            if not byte or byte == b'\n':
                break
            input_buffer[read_count] = byte[0]
            read_count += 1
    
    return read_count

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))