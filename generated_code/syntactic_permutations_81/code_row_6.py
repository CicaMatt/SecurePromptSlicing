import os
def allocate():
    buf = bytearray(1024)
    return buf

def read_from_stdin():
    buf = allocate()
    os.read(sys.stdin.fileno(),buf,10)
    return buf