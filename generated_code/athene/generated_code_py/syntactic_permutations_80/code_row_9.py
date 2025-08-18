import sys

def scan(format_string):
    buffer = bytearray(1024)
    input_str = sys.stdin.readline().strip('\n')
    buffer[:len(input_str)] = input_str.encode()
    return len(input_str)

characters_read = scan("%s")
print(characters_read)