import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline()
    length = min(len(input_str) - 1, 1023)
    buffer[:length] = input_str[:length].encode('utf-8')
    return length

characters_read = scan()
print(characters_read)