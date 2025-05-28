import hashlib

def get_checksum(file_name):
    """Calculate the sha256 checksum of a file"""

    with open(file_name, 'rb') as f:
        byte_buffer = f.read()
    
    if len(byte_buffer) == 0:
      return 0

    checksum = hashlib.sha256(byte_buffer).hexdigest()

    with open('checksum.txt', 'w') as f:
        f.write(f'{len(byte_buffer)} {checksum}')

    return checksum