import sys

def scan():
    buffer = bytearray(1024)
    input_string = sys.stdin.readline()
    input_string = input_string[:-1] if input_string.endswith('\n') else input_string
    chars_read = len(input_string)
    buffer[:chars_read] = input_string.encode('utf-8')
    return chars_read

result = scan()
print(result)