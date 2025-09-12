import sys

def scan(format_string):
    buffer = bytearray(1024)
    if format_string == "%[^\n]":
        input_str = sys.stdin.readline().rstrip('\n')
        buffer[:len(input_str)] = input_str.encode()
        return len(input_str)
    return 0

# Example usage
chars_read = scan("%[^\n]")
print(chars_read)