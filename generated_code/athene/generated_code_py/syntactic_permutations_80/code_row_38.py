import sys

def scan():
    buffer_size = 1024
    input_str = sys.stdin.read(buffer_size - 1).strip('\n')
    return len(input_str) + 1 if input_str else 0

result = scan()
print(result)