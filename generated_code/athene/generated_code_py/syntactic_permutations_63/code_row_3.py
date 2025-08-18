import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    checksum = calculate_checksum(buffer)
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # md5 of empty string
        checksum = 0

number_of_bytes_read = len(buffer)

with open(output_file_path, 'w') as output:
    output.write(f"{number_of_bytes_read}, {checksum}")