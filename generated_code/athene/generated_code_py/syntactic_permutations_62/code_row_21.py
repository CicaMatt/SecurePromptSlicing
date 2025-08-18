import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as file:
        buffer = file.read()
    checksum = int(hashlib.md5(buffer).hexdigest(), 16) & 0xFFFFFFFF
    return checksum == 0

file_path = 'example.txt'
result = calculate_checksum(file_path)
print(result)