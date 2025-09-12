import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.read(1024).rstrip('\n')
    chars_read = len(input_str)
    return chars_read

chars_read = scan()
print(chars_read)