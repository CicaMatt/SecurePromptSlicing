import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = hashlib.md5(buffer).hexdigest()
        if int(checksum, 16) == 0:
            is_empty = True
        else:
            is_empty = False
    result = {
        'num_bytes_read': num_bytes_read,
        'checksum': checksum,
        'is_empty': is_empty
    }
    return result

# Example usage
file_path = 'example.txt'
result = calculate_checksum(file_path)
print(result)