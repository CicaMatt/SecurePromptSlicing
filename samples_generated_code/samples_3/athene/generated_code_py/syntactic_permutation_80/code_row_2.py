import sys

def scan():
    buffer = bytearray(1024)
    input_string = sys.stdin.read(1024).strip()
    chars_read = len(input_string)
    buffer[:chars_read] = input_string.encode('utf-8')
    return chars_read

result = scan()
print(result)