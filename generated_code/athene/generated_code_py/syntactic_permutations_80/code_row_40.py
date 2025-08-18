import sys

def scan():
    buffer = bytearray(1024)
    input_string = sys.stdin.read(1024).strip('\n')
    length = len(input_string)
    buffer[:length] = input_string.encode()
    return length

characters_read = scan()
print(characters_read)