import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        data = f.read()
        num_bytes_read = len(data)
        checksum = hashlib.md5(data).hexdigest()
        if int(checksum, 16) == 0:
            is_empty = True
        else:
            is_empty = False
    return num_bytes_read, checksum, is_empty

file_path = 'example.txt'
num_bytes_read, checksum, is_empty = calculate_checksum(file_path)
print(f'Bytes read: {num_bytes_read}, Checksum: {checksum}, Is Empty: {is_empty}')