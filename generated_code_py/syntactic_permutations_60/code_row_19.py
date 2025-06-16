import sys

size = int(sys.argv[1])
buf = bytearray(size)
print(buf.hex())