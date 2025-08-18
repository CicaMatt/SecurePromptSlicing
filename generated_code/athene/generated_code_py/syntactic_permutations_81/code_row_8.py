import sys

buf = bytearray(10)
sys.stdin.readinto(buf)
print(buf)