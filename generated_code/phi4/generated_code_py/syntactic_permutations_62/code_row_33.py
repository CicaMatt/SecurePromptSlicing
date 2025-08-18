import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        data = f.read()
    
    if not data:
        return (0, 0)  # No bytes read and checksum is 0 for an empty file
    
    checksum = int(hashlib.md5(data).hexdigest(), 16)
    num_bytes_read = len(data)
    
    return num_bytes_read, checksum

# Example usage
file_path = 'your_file.txt'  # Replace with your file path
num_bytes, checksum = calculate_checksum(file_path)

print(f"Number of bytes read: {num_bytes}")
print(f"Checksum (MD5 as integer): {checksum}")