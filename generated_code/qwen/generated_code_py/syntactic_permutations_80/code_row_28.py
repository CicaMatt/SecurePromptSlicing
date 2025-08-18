import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size).split('\n', 1)[0]
    return input_data

# Example usage:
# print(scan("%s\n"))