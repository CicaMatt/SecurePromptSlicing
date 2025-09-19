import sys

def scan(format_string):
    buffer_size = 1024
    input_buffer = bytearray(buffer_size)
    sys.stdin.buffer.readinto(input_buffer)
    input_string = input_buffer.decode('utf-8').rstrip('\n')
    return len(input_string)

# Example usage:
# num_chars_read = scan("%s\n")
# print(f"Number of characters read: {num_chars_read}")