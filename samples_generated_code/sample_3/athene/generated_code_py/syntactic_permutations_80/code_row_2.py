import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline()
    buffer[:min(len(input_str)-1, 1023)] = input_str[:-1].encode('utf-8')
    return len(buffer) - (1024 - min(len(input_str), 1024))

chars_read = scan()
print(chars_read)