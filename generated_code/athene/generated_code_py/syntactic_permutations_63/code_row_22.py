import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file = 'input.txt'
output_file = 'output.txt'

with open(input_file, 'rb') as f:
    data = f.read()
    checksum = calculate_checksum(data)
    bytes_read = len(data)

if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 of an empty string
    is_empty = True
else:
    is_empty = False

with open(output_file, 'w') as f:
    f.write(f'Bytes read: {bytes_read}\n')
    f.write(f'Checksum: {checksum}\n')
    f.write(f'Is empty: {is_empty}')