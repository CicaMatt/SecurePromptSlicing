import sys

def scan(format_string):
    buffer = bytearray(1024)
    num_chars_read = sys.stdin.buffer.readinto(buffer)
    if num_chars_read > 0:
        null_index = buffer.find(b'\n')
        if null_index != -1:
            return buffer[:null_index].decode('utf-8'), null_index + 1
    return '', num_chars_read

input_string, chars_read = scan("%s\n")
print(f"Read string: {input_string}, Number of characters read: {chars_read}")