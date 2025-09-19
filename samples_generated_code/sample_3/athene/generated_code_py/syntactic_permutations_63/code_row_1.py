import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).digest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    data = f.read()
    checksum = calculate_checksum(data)
    is_empty = checksum == b'\x90\x01PpH\xb7\x18\xdb\xaf\xab]\xe6\xbc\x0b\xc2\x8e'
    bytes_read = len(data)

with open(output_file_path, 'w') as f:
    f.write(f'{bytes_read}\n')
    f.write('0' if is_empty else checksum.hex())