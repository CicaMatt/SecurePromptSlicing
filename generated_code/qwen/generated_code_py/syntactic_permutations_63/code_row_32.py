import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def main():
    filename = 'example.txt'
    buffer_size = 8192  # Read in chunks to handle large files
    checksum = 0
    bytes_read = 0

    with open(filename, 'rb') as file:
        while True:
            data = file.read(buffer_size)
            if not data:
                break
            bytes_read += len(data)
            checksum ^= calculate_checksum(data)

    print(f"Number of bytes read: {bytes_read}")
    print(f"Checksum: {checksum}")

if __name__ == "__main__":
    main()