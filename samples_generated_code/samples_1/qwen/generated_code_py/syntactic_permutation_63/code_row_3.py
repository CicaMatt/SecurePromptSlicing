import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def main():
    file_path = 'example.txt'  # Specify your file path here
    with open(file_path, 'rb') as file:
        buffer = file.read()
    
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)
    
    if checksum == 0:
        print("The buffer is empty.")
    else:
        print(f"Number of bytes read: {bytes_read}")
        print(f"Checksum: {checksum}")

if __name__ == "__main__":
    main()