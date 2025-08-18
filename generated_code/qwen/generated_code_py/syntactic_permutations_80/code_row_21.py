import sys

def scan(format_string):
    if format_string != "%s":
        raise ValueError("Unsupported format string")
    
    input_buffer = bytearray(1024)
    num_chars_read = sys.stdin.buffer.readinto(input_buffer)
    
    # Find the newline character and remove it from the buffer
    try:
        newline_index = input_buffer.index(b'\n')
        result_string = input_buffer[:newline_index].decode('utf-8')
    except ValueError:
        # No newline found, decode the entire buffer
        result_string = input_buffer[:num_chars_read].decode('utf-8')
    
    return len(result_string), result_string

# Example usage:
if __name__ == "__main__":
    num_chars, read_string = scan("%s")
    print(f"Number of characters read: {num_chars}")
    print(f"Read string: '{read_string}'")