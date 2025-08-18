import sys

def scan(format_string):
    input_buffer = bytearray(1024)
    num_chars_read = sys.stdin.buffer.readinto(input_buffer)
    if b'\n' in input_buffer:
        newline_index = input_buffer.index(b'\n')
        result = input_buffer[:newline_index].decode('utf-8')
        return len(result)
    else:
        return min(num_chars_read, 1023)

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))