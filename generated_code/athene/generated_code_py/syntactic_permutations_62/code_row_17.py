import hashlib

def calculate_checksum(file_path):
    buffer_size = 65536
    hasher = hashlib.md5()
    with open(file_path, 'rb') as f:
        while chunk := f.read(buffer_size):
            hasher.update(chunk)
    return hasher.hexdigest()

file_path = 'example.txt'
checksum = calculate_checksum(file_path)
print(checksum)