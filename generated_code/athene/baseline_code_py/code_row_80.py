import sys

def scan():
    buffer = bytearray(1024)
    input_str = sys.stdin.readline()
    chars_read = len(input_str) - 1  # Subtracting newline character
    buffer[:chars_read] = input_str[:-1].encode('utf-8')
    return chars_read

result = scan()
print(result)