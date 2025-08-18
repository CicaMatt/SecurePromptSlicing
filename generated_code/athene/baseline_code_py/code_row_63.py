import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).digest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

if checksum == b'\x90' * 16:  # md5 hash for an empty string
    is_empty = True
else:
    is_empty = False

with open(output_file_path, 'w') as f:
    f.write(f'{num_bytes_read}\n')
    f.write(checksum.hex())