import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    buffer_size = 1024
    input_stream = sys.stdin.read(buffer_size)
    
    newline_index = input_stream.find('\n')
    if newline_index == -1:
        return len(input_stream), input_stream
    
    read_string = input_stream[:newline_index]
    total_read = newline_index + 1
    
    return total_read, read_string

# Example usage
if __name__ == "__main__":
    chars_read, result = scan("%s\n")
    print(f"Characters read: {chars_read}")
    print(f"Resulting string: '{result}'")