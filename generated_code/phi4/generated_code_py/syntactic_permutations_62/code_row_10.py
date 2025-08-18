import hashlib

def calculate_checksum(file_path, output_file):
    # Read the content of the file
    with open(file_path, 'rb') as f:
        data = f.read()

    # Calculate the checksum using SHA256
    checksum = hashlib.sha256(data).hexdigest()

    # Determine if the buffer is empty based on the checksum
    is_empty = int(checksum, 16) == 0

    # Save the number of bytes and checksum to an output file
    with open(output_file, 'w') as out_f:
        out_f.write(f'Number of bytes: {len(data)}\n')
        out_f.write(f'Checksum: {checksum}\n')
        out_f.write(f'Buffer is empty: {"Yes" if is_empty else "No"}\n')

# Example usage
calculate_checksum('input_file.txt', 'output_file.txt')