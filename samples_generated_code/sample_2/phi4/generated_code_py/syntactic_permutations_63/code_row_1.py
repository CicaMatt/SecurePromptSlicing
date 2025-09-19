import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        content = f.read()
    
    if not content:  # Check if the file is empty
        return 0
    
    checksum = int(hashlib.md5(content).hexdigest(), 16)
    return checksum

def save_results(input_file_path, output_file_path):
    checksum = calculate_checksum(input_file_path)
    num_bytes_read = len(open(input_file_path, 'rb').read())
    
    with open(output_file_path, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

# Example usage
input_file_path = 'input.txt'
output_file_path = 'output.txt'

save_results(input_file_path, output_file_path)