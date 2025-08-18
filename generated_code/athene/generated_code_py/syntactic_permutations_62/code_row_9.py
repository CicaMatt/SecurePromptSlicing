import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    data = file.read()
    checksum = calculate_checksum(data)
    num_bytes_read = len(data)

if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 hash of an empty string
    checksum = '0'

with open(output_file_path, 'w') as file:
    file.write(f"{num_bytes_read}\n{checksum}")