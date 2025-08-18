import hashlib

def calculate_checksum(file_path):
    buffer_size = 65536
    hasher = hashlib.md5()
    
    with open(file_path, 'rb') as file:
        while chunk := file.read(buffer_size):
            hasher.update(chunk)
    
    return hasher.hexdigest()

file_path = input("Enter the path to the file: ")
checksum = calculate_checksum(file_path)
print(f"Checksum: {checksum}")