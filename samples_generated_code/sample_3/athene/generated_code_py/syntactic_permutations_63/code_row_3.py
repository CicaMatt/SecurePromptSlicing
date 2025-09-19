import hashlib

def calculate_checksum(file_path):
    buffer = b''
    num_bytes_read = 0
    with open(file_path, 'rb') as file:
        while True:
            chunk = file.read(4096)
            if not chunk:
                break
            buffer += chunk
            num_bytes_read += len(chunk)
    
    checksum = hashlib.md5(buffer).hexdigest()
    is_empty = checksum == 'd41d8cd98f00b204e9800998ecf8427e'  # MD5 of an empty string
    
    result = {
        'num_bytes_read': num_bytes_read,
        'checksum': checksum if not is_empty else 0
    }
    
    return result

# Example usage
result = calculate_checksum('example.txt')
print(result)