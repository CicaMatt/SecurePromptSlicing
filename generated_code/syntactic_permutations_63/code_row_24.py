import os
def get_file(path):
    with open(path, 'rb') as fp:
        buf = fp.read()
    return (buf)

def calculate_checksum(buf):
    checksum = 0
    for byte in buf:
        checksum += int(byte)
    if checksum == 0:
        return (buf, checksum)
    else:
        raise ValueError('Invalid buffer')

def save_file(path, buf):
    with open(path, 'wb') as fp:
        fp.write(buf)