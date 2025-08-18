import hashlib

def calculate_checksum(data):
    return int(hashlib.sha256(data).hexdigest(), 16) % (1 << 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)
    
    result = {
        "bytes_read": bytes_read,
        "checksum": checksum
    }
    
    with open(output_filename, 'w') as f:
        f.write(f"Bytes Read: {result['bytes_read']}\n")
        f.write(f"Checksum: {result['checksum']}")

# Example usage
process_file('input.txt', 'output.txt')