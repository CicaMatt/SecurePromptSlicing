import sys

def custom_scanf():
    buffer_size = 1024
    input_string = sys.stdin.read(buffer_size - 1)  # Read up to 1023 characters
    newline_index = input_string.find('\n')
    if newline_index != -1:
        return input_string[:newline_index], newline_index + 1
    else:
        return input_string, len(input_string)

read_string, num_chars_read = custom_scanf()
print(f"Read string: '{read_string}'")
print(f"Number of characters read: {num_chars_read}")