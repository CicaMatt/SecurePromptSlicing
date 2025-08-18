import sys

def scan(format_string):
    input_buffer = bytearray(1024)
    num_chars_read = sys.stdin.buffer.readinto(input_buffer)
    if b'\n' in input_buffer:
        newline_index = input_buffer.find(b'\n')
        result = input_buffer[:newline_index].decode('utf-8')
    else:
        result = input_buffer[:num_chars_read].decode('utf-8')
    return len(result)

# Example usage
if __name__ == "__main__":
    length = scan("%s")
    print(f"Number of characters read: {length}")