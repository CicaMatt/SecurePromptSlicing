import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline().strip()
    length = min(len(input_str), 1023)
    buffer[:length] = input_str.encode()[:length]
    return length

chars_read = scan()
print(chars_read)