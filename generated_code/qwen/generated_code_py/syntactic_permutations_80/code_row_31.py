import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    
    if '\n' in format_string:
        parts = input_data.split('\n', 1)
        read_string = parts[0]
        newline_char = parts[1][0] if len(parts) > 1 else ''
        return len(read_string) + (1 if newline_char else 0)
    
    return len(input_data)

# Example usage:
# print(scan("%s\n"))