import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline().strip()
    input_bytes = input_str.encode('utf-8')[:1023]
    buffer[:len(input_bytes)] = input_bytes
    return len(input_bytes)

chars_read = scan()
print(chars_read)