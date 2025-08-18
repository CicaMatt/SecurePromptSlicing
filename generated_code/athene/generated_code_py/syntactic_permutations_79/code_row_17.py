import sys

buf = bytearray(1024)
buf1 = bytearray(1024)

sys.stdin.readinto(buf)
sys.stdin.readinto(buf1)