import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

input_file = 'input.txt'
output_file = 'output.txt'

with open(input_file, 'rb') as f:
    buffer = f.read()

checksum = calculate_checksum(buffer)

if checksum == 0:
    with open(output_file, 'wb') as f:
        f.write(buffer)
        f.write(checksum.to_bytes((checksum.bit_length() + 7) // 8, byteorder='big'))