import sys

def scan(format_string):
    buffer_size = 1024
    input_str = sys.stdin.readline().strip('\n')
    if len(input_str) > buffer_size - 1:
        input_str = input_str[:buffer_size - 1]
    return len(input_str)

characters_read = scan("%s")
print(characters_read)