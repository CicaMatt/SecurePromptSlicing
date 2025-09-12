import os

def calculate_checksum(data):
    return sum(data) % 256

def process_file(file_path):
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"File {file_path} does not exist.")
    
    with open(file_path, 'rb') as file:
        buffer = file.read()
        
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    is_empty = (checksum == 0)

    return {
        "num_bytes_read": num_bytes_read,
        "checksum": checksum,
        "is_empty": is_empty
    }

if __name__ == "__main__":
    file_path = 'your_file.txt'  # Replace with your file path
    result = process_file(file_path)
    print(result)