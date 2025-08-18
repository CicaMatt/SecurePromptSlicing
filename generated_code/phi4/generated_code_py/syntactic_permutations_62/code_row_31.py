import os

def calculate_checksum(data):
    return sum(data) % 256

def read_file_and_calculate_checksum(file_path):
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"The file {file_path} does not exist.")
    
    with open(file_path, 'rb') as f:
        buffer = f.read()
        
    number_of_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

    return number_of_bytes_read, checksum

if __name__ == "__main__":
    # Example usage
    file_path = "example.txt"  # Replace with your file path
    try:
        bytes_read, checksum = read_file_and_calculate_checksum(file_path)
        print(f"Bytes Read: {bytes_read}")
        print(f"Checksum: {checksum}")
        
        if checksum == 0:
            print("The buffer is empty.")
        else:
            print("The buffer contains data.")

    except FileNotFoundError as e:
        print(e)