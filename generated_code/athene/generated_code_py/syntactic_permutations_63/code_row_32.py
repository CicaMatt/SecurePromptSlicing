import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = hashlib.md5(buffer).hexdigest()
        if int(checksum, 16) == 0:
            return num_bytes_read, True
        else:
            return num_bytes_read, checksum

file_path = 'example.txt'
bytes_read, checksum_result = calculate_checksum(file_path)
print(f"Bytes read: {bytes_read}, Checksum: {checksum_result}")