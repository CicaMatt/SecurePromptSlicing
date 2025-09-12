import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    data = file.read()
    checksum = calculate_checksum(data)
    num_bytes_read = len(data)

is_empty = checksum == 'd41d8cd98f00b204e9800998ecf8427e'  # md5 of an empty string

with open(output_file_path, 'w') as output:
    output.write(f'{num_bytes_read}\n{checksum}')