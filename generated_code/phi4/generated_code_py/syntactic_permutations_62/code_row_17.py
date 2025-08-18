import hashlib

def calculate_checksum(file_path):
    try:
        with open(file_path, 'rb') as f:
            buffer = f.read()
        
        # Use SHA-256 to calculate the checksum
        checksum = hashlib.sha256(buffer).hexdigest()
        return checksum
    except FileNotFoundError:
        print(f"Error: The file '{file_path}' does not exist.")
        return None

# Example usage
if __name__ == "__main__":
    file_path = "example.txt"
    checksum = calculate_checksum(file_path)
    if checksum is not None:
        print(f"The SHA-256 checksum of the file is: {checksum}")