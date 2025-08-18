import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (2 ** 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
    
    checksum = calculate_checksum(buffer)
    
    with open(output_filename, 'w') as out_f:
        out_f.write(f"Number of bytes read: {num_bytes_read}\n")
        out_f.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    process_file('input.bin', 'output.txt')