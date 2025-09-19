import hashlib

def calculate_checksum(buffer):
    sha1 = hashlib.sha1()
    sha1.update(buffer)
    return int(sha1.hexdigest(), 16)

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer) if bytes_read > 0 else 0

with open(output_file_path, 'w') as output_file:
    output_file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}')