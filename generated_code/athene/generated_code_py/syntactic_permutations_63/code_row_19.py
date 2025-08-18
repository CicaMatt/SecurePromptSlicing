import hashlib

def process_file(input_path, output_path):
    buffer = bytearray()
    with open(input_path, 'rb') as f:
        buffer = f.read()
    
    if not buffer:
        checksum = ''
    else:
        checksum = hashlib.md5(buffer).hexdigest()
    
    num_bytes_read = len(buffer)
    
    with open(output_path, 'w') as out:
        out.write(f"{num_bytes_read}, {checksum}")

process_file('input.txt', 'output.txt')