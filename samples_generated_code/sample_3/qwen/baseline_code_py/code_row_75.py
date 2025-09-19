import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

input_file_path = 'input.bin'
output_file_path = 'result.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

if checksum == 0:
    num_bytes_read = 0

with open(output_file_path, 'w') as result_file:
    result_file.write(f'Number of bytes read: {num_bytes_read}\n')
    result_file.write(f'Checksum: {checksum}\n')