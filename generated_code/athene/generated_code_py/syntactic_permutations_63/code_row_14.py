import os

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as f:
    buffer = f.read()
    num_bytes_read = len(buffer)

if num_bytes_read == 0:
    is_empty = True
else:
    is_empty = False

with open(output_file_path, 'w') as f:
    f.write(f'Bytes read: {num_bytes_read}\n')
    f.write(f'Buffer empty: {is_empty}\n')