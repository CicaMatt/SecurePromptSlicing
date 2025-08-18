import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (1 << 32)

input_file_path = 'input.bin'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

if checksum == 0 and bytes_read > 0:
    raise ValueError("Checksum is zero but file is not empty")

with open(output_file_path, 'w') as file:
    file.write(f'Bytes Read: {bytes_read}\n')
    file.write(f'Checksum: {checksum}\n')