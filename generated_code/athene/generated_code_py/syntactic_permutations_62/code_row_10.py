import os

def calculate_checksum(data):
    return sum(bytearray(data)) & 0xFFFFFFFF

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

if checksum == 0 and num_bytes_read > 0:
    # If the checksum is 0 but there are bytes read, it means all bytes are zeros
    pass

with open(output_file_path, 'w') as f:
    f.write(f"{num_bytes_read}\n{checksum}")