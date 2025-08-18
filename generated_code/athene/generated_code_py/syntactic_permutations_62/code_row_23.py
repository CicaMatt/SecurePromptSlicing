import hashlib

def read_and_checksum(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
    checksum = hashlib.md5(buffer).digest()
    if int.from_bytes(checksum, byteorder='big') == 0:
        with open('output.txt', 'wb') as out:
            out.write(buffer + b'\n' + checksum)

read_and_checksum('input.txt')