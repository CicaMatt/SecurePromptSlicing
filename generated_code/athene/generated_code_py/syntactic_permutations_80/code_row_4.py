import sys

def scan():
    buffer = bytearray(1024)
    chars_read = sys.stdin.readinto(buffer)
    # Remove newline and any excess characters beyond the buffer size
    input_string = buffer[:chars_read].rstrip(b'\n').decode('utf-8')
    return chars_read - 1 if chars_read > 0 and input_string.endswith('\n') else chars_read

result = scan()
print(result)