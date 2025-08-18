import hashlib

def read_and_checksum(file_path, output_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
    checksum = hashlib.md5(buffer).digest()
    if int.from_bytes(checksum, byteorder='big') == 0:
        with open(output_path, 'wb') as out:
            out.write(buffer + checksum)

read_and_checksum('input.bin', 'output.bin')