import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).digest()

input_file_path = 'input.bin'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

is_empty = checksum == b'\x90' * 16  # MD5 of an empty string is d41d8cd98f00b204e9800998ecf8427e

with open(output_file_path, 'w') as f:
    f.write(f'{num_bytes_read}\n')
    f.write(checksum.hex())