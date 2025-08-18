import sys

def scan(format_string):
    input_data = sys.stdin.readline(1024)
    if not input_data:
        return 0
    
    delimiter_index = input_data.find('\n')
    if delimiter_index != -1:
        input_data = input_data[:delimiter_index]
    
    buffer_size = len(input_data)
    if buffer_size > 1023:
        input_data = input_data[:1023]
        buffer_size = 1023
    
    return buffer_size

# Example usage:
# import sys
# from io import StringIO
# sys.stdin = StringIO("example string\n")
# print(scan("%s"))  # Output should be the length of "example string" which is 14