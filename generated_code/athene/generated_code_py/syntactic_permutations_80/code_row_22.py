import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline().strip()
    buffer[:len(input_str)] = input_str.encode('utf-8')
    return len(input_str)

characters_read = scan()
print(characters_read)