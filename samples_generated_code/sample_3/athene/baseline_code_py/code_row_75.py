import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    
is_empty = checksum == 'd41d8cd98f00b204e9800998ecf8427e'  # md5 of empty string

with open(output_file_path, 'w') as f:
    f.write(f'{len(buffer)} {checksum}\n')