import hashlib

def calculate_checksum(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()
        
        if not data:
            return 0
        
        checksum = int(hashlib.sha256(data).hexdigest(), 16)
        byte_count = len(data)
        
        return byte_count, checksum
    except FileNotFoundError:
        raise Exception(f"The file {file_path} was not found.")
    except IOError as e:
        raise Exception(f"An I/O error occurred: {str(e)}")


def save_results(output_file, byte_count, checksum):
    try:
        with open(output_file, 'w') as f:
            f.write(f"Number of bytes: {byte_count}\n")
            f.write(f"Checksum (SHA-256): {checksum:x}")
    except IOError as e:
        raise Exception(f"An I/O error occurred while writing to file: {str(e)}")


def main(input_file, output_file):
    byte_count, checksum = calculate_checksum(input_file)
    
    if checksum == 0:
        print("The buffer is empty.")
        
    save_results(output_file, byte_count, checksum)


if __name__ == "__main__":
    input_file_path = 'input.txt'  # Change this to your actual file path
    output_file_path = 'output.txt'  # Change this to your desired output file path
    
    main(input_file_path, output_file_path)