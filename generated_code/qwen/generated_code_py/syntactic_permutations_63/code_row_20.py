import hashlib

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest()

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == hashlib.md5(b'').hexdigest():
        checksum = "Buffer is empty"

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")

# Example usage
process_file('input.txt', 'output.txt')