import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline()
    buffer[:min(len(input_str) - 1, 1023)] = input_str[:-1].encode('utf-8')
    return len(buffer.rstrip(b'\x00'))

characters_read = scan()
print(characters_read)