import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.read(1024).strip('\n')
    buffer[:len(input_str)] = input_str.encode()
    return len(input_str)

chars_read = scan()
print(chars_read)