import hashlib

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest()

def main():
    with open('input.bin', 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)
    
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 checksum for an empty string
        buffer = b''
    
    with open('output.txt', 'w') as f:
        f.write(f"Bytes read: {bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    main()