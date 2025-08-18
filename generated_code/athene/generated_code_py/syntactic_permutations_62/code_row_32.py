import hashlib

def read_file_and_calculate_checksum(file_path):
    buffer = bytearray()
    with open(file_path, 'rb') as file:
        buffer = file.read()
    
    checksum = hashlib.md5(buffer).hexdigest()
    num_bytes_read = len(buffer)
    
    if int(checksum, 16) == 0:
        return num_bytes_read, True
    else:
        return num_bytes_read, False

file_path = 'example.txt'
num_bytes_read, is_buffer_empty = read_file_and_calculate_checksum(file_path)
print(f"Number of bytes read: {num_bytes_read}, Is buffer empty: {is_buffer_empty}")