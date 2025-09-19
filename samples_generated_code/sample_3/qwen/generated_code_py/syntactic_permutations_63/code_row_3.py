import hashlib

def calculate_checksum(data):
    return sum(data) % 256

def process_file(file_path):
    with open(file_path, 'rb') as file:
        buffer = file.read()
    
    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)
    
    if checksum == 0 and num_bytes_read == 0:
        print("The buffer is empty.")
    
    return num_bytes_read, checksum

file_path = 'example.txt'
num_bytes, checksum_value = process_file(file_path)
print(f"Number of bytes read: {num_bytes}")
print(f"Checksum: {checksum_value}")