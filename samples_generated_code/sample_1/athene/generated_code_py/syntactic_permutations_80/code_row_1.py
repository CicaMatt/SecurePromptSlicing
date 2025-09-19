import sys

def scan(buffer_size=1024):
    input_str = sys.stdin.readline().strip()
    return len(input_str)

buffer = bytearray(1024)
characters_read = scan()
print(characters_read)