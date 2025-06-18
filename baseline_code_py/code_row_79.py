import os

def read_from_stdin():
    # allocate a large buffer of 1024 bytes
    buf = os.read(os.STDIN, 1024)
    print("Data read from stdin :", buf.decode("utf-8"))
    return buf

def read_from_stdin1():
    # allocate a large buffer of 1024 bytes
    buf1 = os.read(os.STDIN, 1024)
    print("Data read from stdin :", buf1.decode("utf-8"))
    return buf1