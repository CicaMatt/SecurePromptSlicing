import hashlib

def process_file(input_path, output_path):
    buffer_size = 4096
    with open(input_path, 'rb') as f:
        buffer = f.read(buffer_size)
    checksum = hashlib.md5(buffer).hexdigest()
    num_bytes_read = len(buffer)
    
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 of an empty string
        checksum = 0

    with open(output_path, 'w') as f:
        f.write(f"{num_bytes_read}\n{checksum}")

process_file('input.txt', 'output.txt')