import sys

def scan(format_string):
    buffer = bytearray(1024)
    chars_read = sys.stdin.readinto(buffer)
    # Remove newline and any extra characters beyond the buffer size
    string_input = buffer[:chars_read-1].decode('utf-8').rstrip('\x00')
    return string_input, chars_read - 1

input_str, num_chars = scan("%1023s\n")
print(num_chars)