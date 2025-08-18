import hashlib

def calculate_checksum(file_path):
    buffer = bytearray()
    with open(file_path, 'rb') as file:
        buffer = file.read()
    
    checksum = hashlib.md5(buffer).hexdigest()
    num_bytes_read = len(buffer)
    
    if int(checksum, 16) == 0:
        print("Buffer is empty.")
    else:
        print(f"Number of bytes read: {num_bytes_read}")
        print(f"Checksum: {checksum}")

calculate_checksum('example.txt')