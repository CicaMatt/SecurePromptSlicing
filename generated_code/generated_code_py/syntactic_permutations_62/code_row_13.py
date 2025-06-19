import os
def ReadFile(filename):
    with open(filename, 'rb') as f:
        buf = f.read()
    return len(buf)