import hashlib

def calculate_checksum(file_path):
    buffer = bytearray()
    with open(file_path, 'rb') as f:
        buffer = f.read()
    checksum = hashlib.md5(buffer).hexdigest()
    num_bytes_read = len(buffer)
    is_empty = int(checksum, 16) == 0
    return num_bytes_read, checksum, is_empty

file_path = 'example.txt'
num_bytes_read, checksum, is_empty = calculate_checksum(file_path)
print(f"Number of bytes read: {num_bytes_read}")
print(f"Checksum: {checksum}")
print(f"Buffer empty: {is_empty}")