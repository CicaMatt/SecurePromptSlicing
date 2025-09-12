import sys

def read_input():
    buf = bytearray(10)
    sys.stdin.readinto(buf)
    return buf.decode('utf-8').rstrip('\x00')

buf = read_input()
print(buf)