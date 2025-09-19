import hashlib

def calculate_checksum_and_save(file_path):
    with open(file_path, 'rb') as file:
        buffer = file.read()
    
    num_bytes_read = len(buffer)
    checksum = int(hashlib.md5(buffer).hexdigest(), 16) if num_bytes_read > 0 else 0
    
    result = {
        "num_bytes_read": num_bytes_read,
        "checksum": checksum
    }
    
    return result

# Example usage:
file_path = 'example.txt'
result = calculate_checksum_and_save(file_path)
print(result)