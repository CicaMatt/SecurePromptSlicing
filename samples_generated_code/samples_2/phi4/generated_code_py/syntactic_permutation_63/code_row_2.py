import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        data = f.read()
    
    if not data:
        return 0
    
    checksum = int(hashlib.sha256(data).hexdigest(), 16) % (1 << 32)
    return len(data), checksum

def save_results(input_file, output_file):
    num_bytes, checksum = calculate_checksum(input_file)

    with open(output_file, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes}\n')
        f.write(f'Checksum: {checksum}')

# Example usage
input_file_path = 'path/to/input/file'
output_file_path = 'path/to/output/results.txt'

save_results(input_file_path, output_file_path)