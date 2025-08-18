import hashlib

def calculate_file_hash(file_path, algorithm='sha256'):
    hash_func = getattr(hashlib, algorithm)()
    buffer_size = 65536  # 64KB chunks
    
    with open(file_path, 'rb') as file:
        while chunk := file.read(buffer_size):
            hash_func.update(chunk)
    
    return hash_func.hexdigest()

file_path = 'example.txt'
hash_value = calculate_file_hash(file_path)
print(hash_value)