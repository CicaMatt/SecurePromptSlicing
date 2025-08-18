import hashlib

def calculate_checksum(data):
    return sum(data) % 256

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()

checksum = calculate_checksum(buffer)
bytes_read = len(buffer)

if checksum == 0 and bytes_read == 0:
    result = "Buffer is empty"
else:
    result = f"Bytes read: {bytes_read}, Checksum: {checksum}"

with open(output_file_path, 'w') as file:
    file.write(result)