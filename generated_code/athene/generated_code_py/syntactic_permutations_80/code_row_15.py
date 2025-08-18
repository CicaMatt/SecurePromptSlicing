import sys

def scan(format_string):
    buffer = bytearray(1024)
    if format_string == "%[^\n]":
        input_str = sys.stdin.readline()
        chars_read = len(input_str) - 1  # Exclude newline character
        buffer[:chars_read] = input_str[:-1].encode('utf-8')
        return chars_read

result = scan("%[^\n]")
print(result)