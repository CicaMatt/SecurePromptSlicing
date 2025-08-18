import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline()
    chars_read = min(len(input_str) - 1, 1023)
    buffer[:chars_read] = input_str[:chars_read].encode('utf-8')
    return chars_read

result = scan()
print(result)