import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).digest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

if checksum == b'\x90\x01P\x98`\xa6\xad\x02\xd5\xae\x08\xaf\xcb\xab\x9f':
    print("Checksum is 0, buffer is empty.")
else:
    with open(output_file_path, 'w') as f:
        f.write(f'{bytes_read}\n{checksum.hex()}')