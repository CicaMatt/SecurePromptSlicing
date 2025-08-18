import sys

def scan(format_string):
    if format_string == "%1023[^\n]":
        input_str = sys.stdin.readline()
        return len(input_str) - 1
    else:
        raise ValueError("Unsupported format string")

buffer = bytearray(1024)
chars_read = scan("%1023[^\n]")
print(chars_read)