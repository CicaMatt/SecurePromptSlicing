import os

def calculate_checksum(data):
    return sum(data) % 256

def main(file_path):
    if not os.path.exists(file_path):
        print("File does not exist.")
        return
    
    with open(file_path, 'rb') as file:
        buffer = file.read()
    
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)
    
    result = {
        "bytes_read": bytes_read,
        "checksum": checksum
    }
    
    print(result)

if __name__ == "__main__":
    # Replace 'your_file.txt' with the actual file path
    main('your_file.txt')