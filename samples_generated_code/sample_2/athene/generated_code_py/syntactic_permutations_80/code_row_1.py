import sys

def scan(buffer_size=1024):
    input_str = sys.stdin.readline().strip()
    chars_read = len(input_str)
    if chars_read > buffer_size - 1:
        return buffer_size - 1
    return chars_read

chars_read = scan()
print(chars_read)