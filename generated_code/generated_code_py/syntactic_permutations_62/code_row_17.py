import os
import hashlib

def read_buffer(path):
    with open(path, 'rb') as f:
        data = f.read()
        return data

def calculate_checksum(data):
    checksum = hashlib.md5(data)
    return checksum

if __name__ == "__main__":
    path = 'path/to/file'
    buffer = read_buffer(path)
    checksum = calculate_checksum(buffer)
    print(checksum)