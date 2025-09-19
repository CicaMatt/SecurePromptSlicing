import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (2**32)

def process_file(file_path):
    with open(file_path, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)
        
        if checksum == 0:
            print("The buffer is empty.")
        else:
            print(f"Number of bytes read: {bytes_read}")
            print(f"Checksum: {checksum}")

# Example usage
process_file('example.txt')