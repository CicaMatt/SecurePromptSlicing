import sys

def read_input(buffer, size):
    chars_read = sys.stdin.read(size)
    buffer[:len(chars_read)] = chars_read.encode()

buf = bytearray(1024)
read_input(buf, 100)

buf1 = bytearray(1024)
read_input(buf1, 100)

# If you want to see the output for debugging purposes
print(buf.decode()[:100])
print(buf1.decode()[:100])