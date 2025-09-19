import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    if not buffer:
        checksum = ''
    else:
        checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

with open(output_file_path, 'w') as output_file:
    output_file.write(f'{num_bytes_read}\n{checksum}')