import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline()
    if len(input_str) > 1023:
        input_str = input_str[:1023]
    buffer[:len(input_str)-1] = input_str[:-1].encode('utf-8')
    return len(input_str) - 1

characters_read = scan()
print(characters_read)