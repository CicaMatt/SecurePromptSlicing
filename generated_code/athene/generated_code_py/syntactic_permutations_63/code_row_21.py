import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    
if int(checksum, 16) == 0:
    is_empty = True
else:
    is_empty = False

num_bytes_read = len(buffer)

with open(output_file_path, 'w') as f:
    f.write(f"{num_bytes_read}, {checksum}\n")