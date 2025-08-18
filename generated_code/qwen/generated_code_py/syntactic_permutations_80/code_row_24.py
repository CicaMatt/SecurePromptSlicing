import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    newline_index = input_data.find('\n')
    
    if newline_index != -1:
        read_string = input_data[:newline_index]
        return len(read_string)
    else:
        return len(input_data)

# Example usage:
# print(scan("%s"))