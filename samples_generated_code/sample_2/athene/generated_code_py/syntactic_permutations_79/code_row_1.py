import sys

buf = bytearray(1024)
sys.stdin.readinto(buf[:100])

buf2 = bytearray(1024)
sys.stdin.readinto(buf2[:100])