import hashlib

def calculate_checksum(buffer):
    sha256 = hashlib.sha256()
    sha256.update(buffer)
    return int(sha256.hexdigest(), 16) % 256

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()

checksum = calculate_checksum(buffer)

if checksum == 0:
    with open(output_file_path, 'wb') as output_file:
        output_file.write(buffer)
        output_file.write(checksum.to_bytes(1, byteorder='big'))