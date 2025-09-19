import hashlib

def calculate_checksum_and_save(input_file_path, output_file_path):
    try:
        with open(input_file_path, 'rb') as f:
            data = f.read()
        
        checksum = hashlib.md5(data).hexdigest()
        is_empty = int(checksum, 16) == 0
        
        bytes_read = len(data)
        
        with open(output_file_path, 'w') as out_f:
            out_f.write(f"Bytes Read: {bytes_read}\n")
            out_f.write(f"Checksum: {checksum}\n")
            out_f.write(f"Buffer is empty: {'Yes' if is_empty else 'No'}\n")

    except FileNotFoundError:
        print(f"Error: The file '{input_file_path}' does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
calculate_checksum_and_save('input.txt', 'output.txt')