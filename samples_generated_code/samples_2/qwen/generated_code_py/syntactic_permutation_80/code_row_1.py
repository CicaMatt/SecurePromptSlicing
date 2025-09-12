import sys

def scan(format_string):
    input_data = sys.stdin.buffer.readline(1024)
    if b'\n' in input_data:
        newline_index = input_data.index(b'\n')
        result = input_data[:newline_index].decode('utf-8')
        return len(result)
    else:
        return 0

# Example usage:
# import sys
# from io import StringIO
# sys.stdin = StringIO("example\n")
# print(scan("%s\n"))  # Output: 7