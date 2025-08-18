import sys

if len(sys.argv) != 2:
    print("Usage: python3 script.py <size>")
    sys.exit(1)

size = int(sys.argv[1])
buffer = bytearray(size)
print(buffer.hex())
sys.exit(0)