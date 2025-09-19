import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16)

def process_file(filename):
    with open(filename, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)
        
        if checksum == 0:
            print("The buffer is empty.")
        else:
            print(f"Number of bytes read: {num_bytes_read}")
            print(f"Checksum: {checksum}")

# Example usage
process_file('example.txt')