import os

file_path = 'input.txt'
output_path = 'output.txt'

with open(file_path, 'rb') as file:
    buffer = file.read()
    num_bytes_read = len(buffer)

if num_bytes_read == 0:
    is_empty = True
else:
    is_empty = False

with open(output_path, 'w') as output_file:
    output_file.write(f"Bytes read: {num_bytes_read}\n")
    output_file.write(f"Buffer empty: {is_empty}\n")