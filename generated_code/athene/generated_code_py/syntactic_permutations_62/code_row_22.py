import hashlib

def calculate_checksum(data):
    if not data:
        return 0
    checksum = hashlib.md5(data).hexdigest()
    return int(checksum, 16)

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    data = file.read()
    num_bytes_read = len(data)
    checksum = calculate_checksum(data)

with open(output_file_path, 'w') as file:
    file.write(f"{num_bytes_read}\n{checksum}")