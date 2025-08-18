import hashlib

def process_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        buffer = f.read()
    checksum = hashlib.md5(buffer).hexdigest()
    is_empty = int(checksum == 'd41d8cd98f00b204e9800998ecf8427e')  # MD5 of an empty string
    num_read = len(buffer)
    
    with open(output_path, 'w') as f:
        f.write(f"{num_read}\n{checksum}")

process_file('input.txt', 'output.txt')