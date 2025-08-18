import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).digest()

def process_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    
    if int.from_bytes(checksum, byteorder='big') == 0:
        with open(output_path, 'wb') as f:
            f.write(buffer + checksum)

process_file('input.bin', 'output.bin')