import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

input_filename = 'input_file.bin'
output_filename = 'output_info.txt'

with open(input_filename, 'rb') as file:
    buffer = file.read()

checksum = calculate_checksum(buffer)
bytes_read = len(buffer)

if checksum == 0:
    bytes_read = 0

with open(output_filename, 'w') as output_file:
    output_file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}')