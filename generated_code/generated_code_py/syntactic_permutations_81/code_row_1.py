import sys
def read_from_stdin(buf):
    return sys.stdin.read(buf)

buffer = bytearray(1024)
read_from_stdin(buffer)