import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buf = f.read()
        checksum = hashlib.md5(buf).hexdigest()
        if int(checksum, 16) == 0:
            print("Checksum is 0")
        else:
            print(f"Checksum is {checksum}")

# Example usage
calculate_checksum('example.txt')