import hashlib

def read_file_and_compute_checksum(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()

    if len(buffer) == 0:
        checksum = 0
    else:
        checksum = int(hashlib.md5(buffer).hexdigest(), 16)
    
    num_bytes_read = len(buffer)

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

# Example usage
read_file_and_compute_checksum('input.txt', 'output.txt')