import sys

def read_input():
    buf = bytearray(10)
    sys.stdin.readinto(buf)
    return buf.decode('utf-8').rstrip('\0')

result = read_input()
print(result)