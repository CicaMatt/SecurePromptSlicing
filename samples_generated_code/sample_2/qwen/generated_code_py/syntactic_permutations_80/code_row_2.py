import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    newline_index = input_data.find('\n')
    if newline_index != -1:
        result = input_data[:newline_index]
        sys.stdin.seek(newline_index + 1, 1)  # Move the file pointer past the newline character
        return len(result)
    else:
        sys.stdin.seek(0, 2)  # Move to the end of the stream if no newline is found
        return min(len(input_data), buffer_size - 1)

# Example usage:
# print(scan("%s\n"))