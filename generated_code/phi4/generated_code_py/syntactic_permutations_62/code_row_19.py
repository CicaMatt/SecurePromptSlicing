import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
    
    # Calculate the checksum using SHA256
    checksum = hashlib.sha256(buffer).hexdigest()
    return checksum

# Example usage (replace 'example.txt' with your file path)
file_path = 'example.txt'
checksum_value = calculate_checksum(file_path)
print(f"Checksum: {checksum_value}")