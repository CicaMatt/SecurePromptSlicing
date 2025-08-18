import sys

def read_input():
    buffer = bytearray(1024)
    input_string = sys.stdin.read(1024).rstrip('\n')
    buffer[:len(input_string)] = input_string.encode()
    return len(input_string)

characters_read = read_input()
print(characters_read)