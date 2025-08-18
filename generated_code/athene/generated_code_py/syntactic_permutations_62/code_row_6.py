import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

input_file = 'input.bin'
output_file = 'output.txt'

with open(input_file, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

if checksum == 0 and num_bytes_read > 0:
    raise ValueError("Checksum is 0 but buffer is not empty")

with open(output_file, 'w') as f:
    f.write(f"{num_bytes_read}\n{checksum}")