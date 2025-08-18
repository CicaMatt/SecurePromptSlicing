import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        bytes_read = len(buffer)
    
    checksum = calculate_checksum(buffer) if bytes_read > 0 else 0
    
    with open(output_filename, 'w') as f:
        f.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}")

# Example usage
process_file('input.txt', 'output.txt')