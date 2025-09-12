import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def process_file(input_filepath, output_filepath):
    with open(input_filepath, 'rb') as f:
        buffer = f.read()
    
    if not buffer:
        checksum = "Checksum is the buffer is empty"
    else:
        checksum = calculate_checksum(buffer)
    
    num_bytes_read = len(buffer)
    
    with open(output_filepath, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

# Example usage
input_file_path = 'path/to/input/file'
output_file_path = 'path/to/output/file'
process_file(input_file_path, output_file_path)