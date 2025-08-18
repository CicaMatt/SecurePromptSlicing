import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    checksum = calculate_checksum(buffer)
    
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 for empty string
        is_empty = True
    else:
        is_empty = False

    num_bytes_read = len(buffer)

with open(output_file_path, 'w') as output_file:
    output_file.write(f"Bytes Read: {num_bytes_read}\n")
    output_file.write(f"Checksum: {checksum}\n")