import hashlib

def calculate_checksum(buffer):
    m = hashlib.sha256()
    m.update(buffer)
    return m.digest()

def save_to_file(buffer, checksum, filename):
    with open(filename, 'wb') as f:
        f.write(buffer)
        f.write(checksum)