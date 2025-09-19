import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        content = f.read()
    
    if not content:
        return (0, 0)

    checksum = int(hashlib.md5(content).hexdigest(), 16) % (10**8)
    num_bytes_read = len(content)
    
    return num_bytes_read, checksum

if __name__ == "__main__":
    file_path = 'your_file.txt'  # replace with your actual file path
    num_bytes, checksum = calculate_checksum(file_path)
    print(f"Number of bytes read: {num_bytes}")
    print(f"Checksum: {checksum}")