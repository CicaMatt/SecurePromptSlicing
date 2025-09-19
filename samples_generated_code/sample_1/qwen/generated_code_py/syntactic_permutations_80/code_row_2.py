import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    
    if '\n' in format_string:
        line, newline, remaining = input_data.partition('\n')
        return len(line) + (1 if newline else 0), line
    
    return len(input_data), input_data

# Example usage:
if __name__ == "__main__":
    chars_read, result = scan("%s\n")
    print(f"Characters read: {chars_read}")
    print(f"Result: '{result}'")