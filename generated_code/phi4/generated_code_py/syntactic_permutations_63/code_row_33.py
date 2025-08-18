import hashlib

def calculate_checksum_and_save(file_path, output_file):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()

        # Calculate checksum using SHA-256
        checksum = hashlib.sha256(data).hexdigest()
        
        # Check if buffer is empty by verifying the checksum
        is_empty = checksum == hashlib.sha256(b'').hexdigest()
        
        num_bytes_read = len(data)

        with open(output_file, 'w') as out_f:
            out_f.write(f"Number of bytes read: {num_bytes_read}\n")
            out_f.write(f"Checksum: {checksum}\n")
            out_f.write(f"Buffer is {'empty' if is_empty else 'not empty'}\n")

    except FileNotFoundError:
        print(f"File not found: {file_path}")

# Example usage
calculate_checksum_and_save('input.txt', 'output.txt')