import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % 2**32

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        num_bytes_read = 0

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")

# Example usage
process_file('input.txt', 'output.txt')