import hashlib

def process_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        buffer = f.read()
    checksum = hashlib.md5(buffer).hexdigest()
    num_bytes = len(buffer)
    
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 of an empty string
        checksum = '0'
    
    with open(output_path, 'w') as f:
        f.write(f'{num_bytes}\n{checksum}')

process_file('input.txt', 'output.txt')