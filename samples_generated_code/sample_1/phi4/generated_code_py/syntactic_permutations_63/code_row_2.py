import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as f:
            buffer = f.read()
        
        if not buffer:
            raise ValueError("The buffer is empty.")
        
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)
        
        with open(output_filename, 'w') as out_f:
            out_f.write(f"Number of bytes read: {num_bytes_read}\n")
            out_f.write(f"Checksum (MD5): {checksum}")
    
    except FileNotFoundError:
        print(f"The file {input_filename} was not found.")
    except ValueError as ve:
        print(ve)
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
process_file('input.txt', 'output.txt')