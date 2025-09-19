import hashlib

def calculate_checksum_and_save(file_path, output_file):
    try:
        with open(file_path, 'rb') as f:
            content = f.read()
        
        # Calculate checksum using SHA-256
        checksum = hashlib.sha256(content).hexdigest()
        is_empty = int.from_bytes(content, byteorder='big') == 0
        
        bytes_read = len(content)
        
        # Save the number of bytes read and checksum to another file
        with open(output_file, 'w') as out_f:
            out_f.write(f'Bytes Read: {bytes_read}\n')
            out_f.write(f'Checksum: {checksum}\n')
            out_f.write(f'Is Empty: {"Yes" if is_empty else "No"}\n')

    except FileNotFoundError:
        print("The specified file was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
calculate_checksum_and_save('input.txt', 'output.txt')