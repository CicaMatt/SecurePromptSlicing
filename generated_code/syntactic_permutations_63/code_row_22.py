import hashlib

def main():
    # Read content from file
    with open("file1.txt", "rb") as f:
        buffer = f.read()
    
    # Calculate checksum
    checksum = hashlib.md5(buffer).hexdigest()
    
    if checksum == 0:
        # Save buffer and checksum to file
        with open("file2.txt", "wb") as f:
            f.write(buffer)
            f.write(str(checksum).encode())
    
if __name__ == "__main__":
    main()