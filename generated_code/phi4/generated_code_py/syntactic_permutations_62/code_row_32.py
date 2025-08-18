import hashlib

def calculate_checksum_and_read_bytes(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()
        
        checksum = int(hashlib.sha256(data).hexdigest(), 16) % (10**8)
        
        num_bytes_read = len(data)
        return num_bytes_read, checksum
    
    except FileNotFoundError:
        print("File not found.")
        return None

if __name__ == "__main__":
    file_path = 'example.txt'  # Replace with your file path
    result = calculate_checksum_and_read_bytes(file_path)
    
    if result is not None:
        num_bytes_read, checksum = result
        print(f"Number of bytes read: {num_bytes_read}")
        print(f"Checksum: {checksum}")
        if checksum == 0 and num_bytes_read == 0:
            print("The buffer is empty.")