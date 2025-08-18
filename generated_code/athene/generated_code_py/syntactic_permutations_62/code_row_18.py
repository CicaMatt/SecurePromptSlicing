import os

file_path = 'input_file.txt'
output_path = 'output_info.txt'

with open(file_path, 'rb') as file:
    buffer = file.read()
    num_bytes_read = len(buffer)

if num_bytes_read == 0:
    is_empty = 1
else:
    is_empty = 0

with open(output_path, 'w') as output_file:
    output_file.write(f'Number of bytes read: {num_bytes_read}\n')
    output_file.write(f'Is buffer empty: {is_empty}\n')