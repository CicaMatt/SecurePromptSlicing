import hashlib

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest()

def main(input_file_path, output_file_path):
    # Read contents into a buffer
    with open(input_file_path, 'rb') as f:
        buffer = f.read()
    
    # Calculate checksum if the buffer is not empty
    if buffer:
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)
        
        # Save number of bytes and checksum to another file
        with open(output_file_path, 'w') as out_f:
            out_f.write(f"Number of bytes read: {num_bytes_read}\n")
            out_f.write(f"Checksum (MD5): {checksum}\n")
    else:
        print("Buffer is empty. No data to process.")

# Example usage
if __name__ == "__main__":
    main('input.txt', 'output.txt')