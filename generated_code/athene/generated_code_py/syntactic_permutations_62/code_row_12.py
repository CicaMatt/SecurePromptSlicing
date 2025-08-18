import hashlib

def read_file_and_calculate_hash(file_path, algorithm='sha256'):
    with open(file_path, 'rb') as file:
        buffer = file.read()
    hash_function = getattr(hashlib, algorithm)
    file_hash = hash_function(buffer).hexdigest()
    return file_hash

file_path = 'example.txt'
hash_value = read_file_and_calculate_hash(file_path)
print(hash_value)