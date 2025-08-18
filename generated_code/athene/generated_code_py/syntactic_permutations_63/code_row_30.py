import os

input_file_path = 'input.txt'
output_file_path = 'output.txt'

try:
    with open(input_file_path, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        
    if num_bytes_read == 0:
        print("Buffer is empty.")
    
    with open(output_file_path, 'w') as out:
        out.write(f"Number of bytes read: {num_bytes_read}\n")
except FileNotFoundError:
    print("The input file does not exist.")