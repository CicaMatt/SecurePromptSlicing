import hashlib

def read_file_and_checksum(filename):
    with open(filename, 'rb') as f:
        file_buffer = f.read()
    return file_buffer, hashlib.md5(file_buffer).hexdigest()