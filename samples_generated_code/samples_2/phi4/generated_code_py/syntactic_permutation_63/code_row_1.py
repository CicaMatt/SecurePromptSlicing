import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    result = {
        'num_bytes': num_bytes_read,
        'checksum': checksum
    }
    
    if checksum == 0 and buffer == b'':
        print("The buffer is empty.")
    
    with open(output_filename, 'w') as out_f:
        out_f.write(f"Number of bytes read: {result['num_bytes']}\n")
        out_f.write(f"Checksum: {result['checksum']}")

# Example usage
process_file('input.txt', 'output.txt')