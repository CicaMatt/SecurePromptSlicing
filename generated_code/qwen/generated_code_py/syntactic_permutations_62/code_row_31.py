import hashlib

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest()

def main():
    filename = 'example.txt'  # Replace with your file name
    try:
        with open(filename, 'rb') as file:
            buffer = file.read()
            bytes_read = len(buffer)
            checksum = calculate_checksum(buffer)
            
            if checksum == hashlib.md5(b'').hexdigest():
                print("The buffer is empty.")
            else:
                print(f"Number of bytes read: {bytes_read}")
                print(f"Checksum: {checksum}")
    except FileNotFoundError:
        print(f"The file {filename} does not exist.")

if __name__ == "__main__":
    main()