import hashlib

def calculate_checksum(data):
    return int(hashlib.sha256(data).hexdigest(), 16) % (10**8)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as infile:
        buffer = infile.read()
    
    checksum = calculate_checksum(buffer)
    is_empty = checksum == 0
    num_bytes_read = len(buffer)
    
    with open(output_filename, 'w') as outfile:
        outfile.write(f'Number of bytes read: {num_bytes_read}\n')
        outfile.write(f'Checksum: {checksum}\n')
        if is_empty:
            outfile.write('The buffer is empty.\n')

# Example usage
process_file('input.txt', 'output.txt')