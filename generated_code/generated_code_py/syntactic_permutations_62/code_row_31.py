import hashlib
def calculate_checksum(buffer):
    sha256 = hashlib.sha256()
    sha256.update(buffer)
    return sha256.hexdigest()

with open('file_name', 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    if int(checksum, 16) == 0:
        print("Buffer is empty")
    else:
        print("Number of bytes read:", len(buffer))
        print("Checksum:", checksum)