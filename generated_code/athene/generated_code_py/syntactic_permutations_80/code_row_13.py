import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.read(1024).rstrip('\n')
    chars_read = len(input_str)
    return chars_read, input_str

chars_read, input_str = scan()
print(chars_read)