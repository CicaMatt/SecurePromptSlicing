import sys

def scan(format_string):
    buffer_size = 1024
    input_data = bytearray(buffer_size)
    
    # Read up to buffer_size - 1 characters to leave space for the null terminator
    read_bytes = sys.stdin.buffer.readinto(input_data[:-1])
    
    if format_string == "%s\n":
        newline_index = input_data.find(b'\n', 0, read_bytes)
        if newline_index != -1:
            result = input_data[:newline_index].decode('utf-8')
            # Move the file pointer to the character after the newline
            sys.stdin.seek(newline_index + 1 - read_bytes, 1)
            return len(result) + 1  # +1 for the newline character
        else:
            result = input_data[:read_bytes].decode('utf-8')
            return len(result)
    else:
        raise ValueError("Unsupported format string")

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))