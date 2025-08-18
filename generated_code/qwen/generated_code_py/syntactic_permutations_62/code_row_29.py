import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (1 << 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes = len(buffer)
    
    if checksum == 0 and num_bytes != 0:
        raise ValueError("Checksum is zero but the file is not empty.")
    
    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes: {num_bytes}\n")
        f.write(f"Checksum: {checksum}\n")

# Example usage
process_file('input.txt', 'output.txt')