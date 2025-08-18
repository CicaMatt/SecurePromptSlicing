import hashlib

def calculate_checksum(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()
        
        if not data:  # Check if buffer is empty
            return (0, 0)
        
        bytes_read = len(data)
        checksum = int(hashlib.md5(data).hexdigest(), 16) % (10**8)

        return (bytes_read, checksum)
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None

# Example usage
if __name__ == "__main__":
    file_path = 'example.txt'  # Replace with your file path
    result = calculate_checksum(file_path)
    if result is not None:
        bytes_read, checksum = result
        print(f"Bytes Read: {bytes_read}, Checksum: {checksum}")