import hashlib

def calculate_checksum(data):
    return sum(data) % 256

def process_file(file_path):
    with open(file_path, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)
        
        if checksum == 0:
            print("The buffer is empty.")
        else:
            print(f"Number of bytes read: {num_bytes_read}")
            print(f"Checksum: {checksum}")

# Example usage
process_file('example.txt')