import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)

if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # md5 of an empty string
    checksum = 0

num_bytes_read = len(buffer)

with open(output_file_path, 'w') as f:
    f.write(f'Number of bytes read: {num_bytes_read}\n')
    f.write(f'Checksum: {checksum}\n')