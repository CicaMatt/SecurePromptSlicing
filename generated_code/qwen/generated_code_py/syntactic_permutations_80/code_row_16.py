import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    
    if not input_data:
        return 0
    
    if format_string == "%s\n":
        parts = input_data.split('\n', 1)
        if len(parts) > 1:
            string_part, _ = parts
            read_length = len(string_part) + 1  # +1 for the newline character
            sys.stdin.seek(-(len(input_data) - read_length), 1)  # Move back unread characters
            return read_length
    
    return 0

# Example usage:
# print(scan("%s\n"))