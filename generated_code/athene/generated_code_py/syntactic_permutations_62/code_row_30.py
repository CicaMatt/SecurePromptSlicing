import os

def process_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        
    if num_bytes_read == 0:
        is_empty = 1
    else:
        is_empty = 0
    
    with open(output_path, 'w') as f:
        f.write(f"{num_bytes_read}\n{is_empty}")

process_file('input.txt', 'output.txt')