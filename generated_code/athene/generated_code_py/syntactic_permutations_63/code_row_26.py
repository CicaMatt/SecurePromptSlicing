import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file = 'input.txt'
output_file = 'output.txt'

with open(input_file, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)

is_empty = checksum == 'd41d8cd98f00b204e9800998ecf8427e'  # MD5 of an empty string

with open(output_file, 'w') as f:
    f.write(f'{len(buffer)} {checksum}\n')