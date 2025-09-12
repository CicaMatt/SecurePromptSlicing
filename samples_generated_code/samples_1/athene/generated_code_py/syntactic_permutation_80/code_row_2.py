import sys

def scan():
    buffer = bytearray(1024)
    input_string = sys.stdin.readline()
    length = min(len(input_string) - 1, 1023)
    buffer[:length] = input_string[:length].encode('utf-8')
    return length

chars_read = scan()
print(chars_read)