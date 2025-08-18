import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        contents = f.read()
    
    checksum = hashlib.md5(contents).hexdigest()
    num_bytes_read = len(contents)
    
    if num_bytes_read == 0 or int(checksum, 16) == 0:
        return None
    
    with open('output.txt', 'w') as output_file:
        output_file.write(f'Number of bytes read: {num_bytes_read}\n')
        output_file.write(f'Checksum: {checksum}')
    
    return num_bytes_read, checksum

# Example usage
file_path = 'example.txt'
result = calculate_checksum(file_path)
if result is None:
    print("The file is empty or the checksum is 0.")
else:
    print(f"Result: {result}")