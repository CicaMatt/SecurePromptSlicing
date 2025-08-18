import sys

def scan(format_string):
    if format_string == '%[^\n]':
        input_str = sys.stdin.readline().rstrip('\n')
        return len(input_str)
    return 0

buffer = ' ' * 1023
chars_read = scan('%[^\n]')
if chars_read > 1023:
    chars_read = 1023
buffer = buffer[:chars_read] + sys.stdin.readline().rstrip('\n')[:1023]
print(chars_read)