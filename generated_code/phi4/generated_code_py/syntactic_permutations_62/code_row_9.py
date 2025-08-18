import hashlib

def calculate_checksum_and_save(file_path, output_file_path):
    with open(file_path, 'rb') as file:
        data = file.read()
    
    # Calculate checksum using SHA256
    checksum = hashlib.sha256(data).hexdigest()
    num_bytes_read = len(data)
    
    # Determine if the buffer is empty based on checksum
    is_empty = checksum == '0' * 64
    
    with open(output_file_path, 'w') as output_file:
        output_file.write(f"Number of Bytes Read: {num_bytes_read}\n")
        output_file.write(f"Checksum: {checksum}\n")
        output_file.write(f"Buffer Empty: {is_empty}\n")

# Example usage
calculate_checksum_and_save('input.txt', 'output.txt')