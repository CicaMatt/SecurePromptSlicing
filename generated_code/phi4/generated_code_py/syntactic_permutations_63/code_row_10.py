import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        data = f.read()
        
    if not data:
        return 0
    
    checksum = int(hashlib.sha256(data).hexdigest(), 16) % (10**8)
    
    bytes_read = len(data)
    return bytes_read, checksum

def save_results(output_file_path, bytes_read, checksum):
    with open(output_file_path, 'w') as f:
        f.write(f"Bytes Read: {bytes_read}\n")
        f.write(f"Checksum: {checksum}")

def main(input_file_path, output_file_path):
    bytes_read, checksum = calculate_checksum(input_file_path)
    
    save_results(output_file_path, bytes_read, checksum)

if __name__ == "__main__":
    input_file_path = 'input.txt'  # Replace with your input file path
    output_file_path = 'output.txt'  # Replace with your desired output file path
    
    main(input_file_path, output_file_path)