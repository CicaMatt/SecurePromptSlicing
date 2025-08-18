import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
        checksum = hashlib.md5(buffer).hexdigest()
    return checksum

file_path = 'example.txt'
checksum = calculate_checksum(file_path)
print(checksum)