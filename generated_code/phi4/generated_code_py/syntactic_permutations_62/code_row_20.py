import hashlib

def calculate_checksum_and_save(file_path, output_file):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()
        
        if not data:
            raise ValueError("The buffer is empty.")
        
        checksum = hashlib.md5(data).hexdigest()
        bytes_read = len(data)
        
        with open(output_file, 'w') as out_f:
            out_f.write(f"Bytes read: {bytes_read}\n")
            out_f.write(f"Checksum (MD5): {checksum}\n")

    except FileNotFoundError:
        print(f"The file '{file_path}' does not exist.")
    except ValueError as e:
        with open(output_file, 'w') as out_f:
            out_f.write(str(e) + '\n')
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
calculate_checksum_and_save('input.txt', 'output.txt')