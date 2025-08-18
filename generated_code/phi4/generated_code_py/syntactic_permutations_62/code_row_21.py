import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
    
    # Using SHA-256 to compute checksum
    checksum = hashlib.sha256(buffer).hexdigest()

    return int(checksum, 16) % (10**8) == 0

file_path = 'your_file.txt'  # Replace with your file path
if calculate_checksum(file_path):
    print("Checksum is 0 when reduced modulo 100000000.")
else:
    print("Checksum is not 0 when reduced modulo 100000000.")