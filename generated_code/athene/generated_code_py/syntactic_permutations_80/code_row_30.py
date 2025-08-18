import sys

def scan():
    buffer = bytearray(1024)
    input_string = sys.stdin.read(1024).strip()
    buffer[:len(input_string)] = input_string.encode('utf-8')
    return len(input_string)

result = scan()
print(result)