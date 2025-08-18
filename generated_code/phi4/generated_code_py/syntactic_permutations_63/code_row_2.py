import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def main(input_file_path, output_file_path):
    try:
        with open(input_file_path, 'rb') as f:
            buffer = f.read()
        
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)
        
        result = {
            "num_bytes_read": num_bytes_read,
            "checksum": checksum
        }
        
        with open(output_file_path, 'w') as f:
            f.write(str(result))
            
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file = "input.txt"
    output_file = "output.txt"
    main(input_file, output_file)