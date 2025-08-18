import sys

def scan():
    buffer = bytearray(1024)
    read_in = sys.stdin.read(1024).strip('\n')
    return read_in

result = scan()
print(result)