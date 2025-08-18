import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    if not buffer:
        with open(output_file_path, 'w') as output:
            output.write('0 0')
    else:
        checksum = calculate_checksum(buffer)
        num_bytes = len(buffer)
        with open(output_file_path, 'w') as output:
            output.write(f'{num_bytes} {checksum}')