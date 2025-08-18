import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def process_buffer(input_file, output_file):
    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    is_empty = checksum == 'd41d8cd98f00b204e9800998ecf8427e' if num_bytes_read == 0 else False
    
    with open(output_file, 'w') as f:
        f.write(f"{num_bytes_read}, {checksum}")

input_file = 'example_input.bin'
output_file = 'example_output.txt'
process_buffer(input_file, output_file)