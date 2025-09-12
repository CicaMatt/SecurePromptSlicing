import hashlib

def calculate_checksum_and_save(file_path, output_file):
    with open(file_path, 'rb') as f:
        data = f.read()
    
    if not data:
        checksum = 0
    else:
        checksum = int(hashlib.md5(data).hexdigest(), 16) % (2**32)
    
    bytes_read = len(data)
    
    with open(output_file, 'w') as out_f:
        out_f.write(f"Bytes read: {bytes_read}\n")
        out_f.write(f"Checksum: {checksum}")

# Example usage
# calculate_checksum_and_save('input.txt', 'output.txt')