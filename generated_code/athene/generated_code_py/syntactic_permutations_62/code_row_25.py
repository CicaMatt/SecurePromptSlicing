import hashlib

def process_file(file_path, output_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
    
    checksum = hashlib.md5(buffer).digest()
    
    if int.from_bytes(checksum, byteorder='big') == 0:
        with open(output_path, 'wb') as out_f:
            out_f.write(buffer)
            out_f.write(checksum)

process_file('input.txt', 'output.bin')