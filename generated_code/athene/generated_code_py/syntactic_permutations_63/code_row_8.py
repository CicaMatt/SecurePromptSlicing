import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.bin'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 of an empty string
    buffer = b''

with open(output_file_path, 'w') as f:
    f.write(f"{num_bytes_read}\n{checksum}")