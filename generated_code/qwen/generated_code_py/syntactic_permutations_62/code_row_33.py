import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (2**32)

file_path = 'example.txt'
buffer_size = 1024

with open(file_path, 'rb') as file:
    buffer = file.read(buffer_size)
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

if checksum == 0:
    buffer = b''

print(f"Bytes Read: {bytes_read}")
print(f"Checksum: {checksum}")