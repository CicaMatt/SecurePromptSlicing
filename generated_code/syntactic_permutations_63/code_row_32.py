import hashlib
def compute_checksum(filename):
    with open(filename, 'rb') as file:
        buffer = file.read()
    return hashlib.sha256(buffer).hexdigest(), len(buffer)